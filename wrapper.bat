@echo off

rem bukkonuki�̃��b�p�[�X�N���v�g�A�o�C�i���Ɠ����f�B���N�g���ɓ���Ă�������
rem D&D�ł�ł�񂱂݂����Ȋ����ɂ�����

rem D&D���ꂽ�p�X�̃o�b�N�X���b�V�����X���b�V���ɒu��
set dropped_path=%1
set input_path=%dropped_path:\=/%

echo "���̓p�X��"%input_path%

rem �t�@�C���������ɏo�̓t�H���_�쐬
set filename=%~n1
set output_dir=%filename: =_%
mkdir %~dp0\slides > NUL 2>&1
mkdir %~dp0\slides\%output_dir%
set made_dir=%~dp0slides\%output_dir%
set output_path=%made_dir:\=/%/
echo %output_path%


rem ����̃A�X�y�N�g�������
set aspect=
set /P aspect="����̉�ʔ�́H(4:3�Ȃ�0 / 16:9�Ȃ�1)�F"

rem Auto���[�h�ɂ��邩
choice /m "�S�ăf�t�H���g�ݒ�ŏ������܂���?(y/n)"

if errorlevel 2 goto :manual
if errorlevel 1 goto :auto

:auto
set trimming=0
set threshold=10
set interval=5

rem �Ԃ����ʂ����s
call %~dp0Slidebukkonuki_wintest.exe %input_path% %output_path% %threshold% %trimming% %aspect% %interval% 
exit /b

:manual
rem �g���~���O�w��
set trimming=
set /P trimming="�g���~���O���܂����H(�f�t�H���g�Ȃ�0)"

rem 臒l�w��
set threshold=
set /P threshold="臒l���w�肵�܂���?(�f�t�H���g�Ȃ�10)"

rem �t���[���擾�Ԋu
set interval=
set /P interval="�t���[���擾�Ԋu��ύX���܂����H(�f�t�H���g�Ȃ�5)"

rem �Ԃ����ʂ����s
call %~dp0Slidebukkonuki_wintest.exe %input_path% %output_path% %threshold% %trimming% %aspect% %interval% 

exit /b

