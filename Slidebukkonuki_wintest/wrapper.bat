rem bukkonuki�̃��b�p�[�X�N���v�g�A�o�C�i���Ɠ����f�B���N�g���ɓ���Ă�������
rem D&D�ł�ł�񂱂݂����Ȋ����ɂ�����
@echo off

rem D&D���ꂽ�p�X�̃o�b�N�X���b�V�����X���b�V���ɒu��
set dropped_path=%1

set input_path=%dropped_path:\=/%
echo %input_path%

rem �t�@�C���������ɏo�̓t�H���_�쐬
set filename=%~n1
set output_dir=%filename: =_%
mkdir %~dp0\slides
mkdir %~dp0\slides\%output_dir%
set made_dir=%~dp0\slides\%output_dir%

set output_path="%made_dir:\=/%"

rem ����̃A�X�y�N�g�������
set aspect=
set /P aspect="����̉�ʔ�́H(4:3�Ȃ�0 / 16:9�Ȃ�1)�F"
echo %aspect%
pause