#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>

using namespace cv;

std::string g_save_location = "./";
// 臒l�@��%�̍����ŏ������邩
float g_threshold = 10.0;
// ���b�Ԋu�œ�����������邩
int g_interval = 5;
// �g���~���O�J�n�ʒu
int g_trimming_point = 0;
// �X���C�h�̃A�X�y�N�g��(0�Ȃ�4:3,1�Ȃ�16:9)
int g_aspect_ratio = 0;

// �g���~���O����
Mat trimming(Mat frame)
{
	int height = frame.rows;
	// �g���~���O������B
	if (g_aspect_ratio == 0)
	{
		// 4:3
		Rect roi(Point(g_trimming_point, 0), Size((height / 3) * 4, height));
		return frame(roi);
	}
	else
	{
		// 16:9
		Rect roi(Point(g_trimming_point, 0), Size((height / 9) * 16, height));
		return frame(roi);
	}
}

// �t���[���Ԃł̍������v�Z����
Mat difference(Mat frame1, Mat frame2)
{
	// �����̐�Βl
	Mat sabun = abs(frame1 - frame2);
	Mat output;
	// �t�B���^�[�������ĕ��R��
	medianBlur(sabun, output, 25);
	return output;
}

// �������ǂ̒��x�̑傫���Ȃ̂����v�Z����臒l���傫�����True
bool compare_frames(Mat frame)
{
	int width = frame.cols;
	int height = frame.rows;

	long int count = 0;
	long int countRGB = 0;
	for (int i = height / 4; i < height * 3 / 4; i += 5)
	{
		for (int j = width / 4; j < width * 3 / 4; j += 5)
		{
			count++;
			countRGB += (frame.at<Vec3b>(i, j)[0] + frame.at<Vec3b>(i, j)[1] + frame.at<Vec3b>(i, j)[2]);
		}
	}

	// printf("RGB���v�F%ld\n", countRGB);
	// printf("�����񐔁F%ld\n", count);
	// printf("���ρF%ld \n", countRGB / count);
	printf("�ω������F%f\n", ((float)(countRGB / count) / 256) * 100);

	// �w�肵��臒l�����ω����Ă��邩
	return ((((float)(countRGB / count) / 256) * 100) > g_threshold);
}

// �Q�l:https://kisqragi.hatenablog.com/entry/2019/11/02/130921
// ��1����:���r�f�I�̃p�X
int movie_to_picture(std::string video_path)
{
	VideoCapture video(video_path);
	// ���悪�Ȃ��ꍇ
	if (!video.isOpened())
	{
		return -1;
	}
	// �t���[�����擾
	int frame_num = video.get(cv::CAP_PROP_FRAME_COUNT);
	// 00x.ext �ɂ��邽�߂̌����̎擾
	int digit = std::to_string(frame_num).length();

	Mat frame1;
	//frame1�ɓK���ȉ摜��}�����鏈��
	video.set(CAP_PROP_POS_FRAMES, frame_num - 10);
	video >> frame1;

	Mat frame2;

	int fps = video.get(cv::CAP_PROP_FPS);

	for (int i = 0; i < frame_num; i += fps * g_interval)
	{
		if (i > 0)
		{
			// �t���[�����w�肵���b�������炷
			video.set(CAP_PROP_POS_FRAMES, i - fps * g_interval);
			// �t���[�����擾����
			video >> frame1;
		}
		frame1 = trimming(frame1);

		// �t���[�����w�肵���b�������炷
		video.set(CAP_PROP_POS_FRAMES, i);
		// �t���[�����擾����
		video >> frame2;
		frame2 = trimming(frame2);

		if (frame2.empty())
		{
			return -1;
		}

		if (compare_frames(difference(frame1, frame2)))
		{
			// 00x.ext�̕�����쐬
			std::stringstream ss;
			ss << g_save_location << std::setw(digit) << i << ".jpg";
			std::cout << ss.str() << std::endl;
			// �ۑ�����
			imwrite(ss.str().c_str(), frame2);
		}
	}

	return 0;
}

int main(int argc, char *argv[])
{
	std::string input_location = argv[1];
	g_save_location = argv[2];
	g_threshold = atof(argv[3]);
	g_trimming_point = atoi(argv[4]);
	g_aspect_ratio = atoi(argv[5]);
	g_interval = atoi(argv[6]);

	printf("**********�ݒ�m�F**********\n");
	printf("臒l:%f\n", g_threshold);
	printf("�g���~���O�J�n�ʒu:%d\n", g_trimming_point);
	printf("�X���C�h�擾�Ԋu:%d�b\n", g_interval);
	printf("�A�X�y�N�g��:");
	if (g_aspect_ratio == 0)
	{
		printf("4:3\n");
	}
	else
	{
		printf("16:9\n");
	}
	printf("**********�ݒ�m�F�I���**********\n\n");
	movie_to_picture(input_location);
	return 0;
}