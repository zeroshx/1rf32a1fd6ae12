#include "DialogBuilder.h"

DialogBuilder::DialogBuilder()
{

}
DialogBuilder::~DialogBuilder()
{

}
Dialog* DialogBuilder::build(int type)
{
	auto dialog = Dialog::create();

	switch (type)
	{

	case BUILD_TYPE_LOGIN_FAILURE:
	{
		dialog->setTitle("로그인 실패");
		dialog->setMessage("네트워크 상태 확인 및 선택하신 로그인 서비스가 사용 가능한지 확인해주세요. 문제가 지속될 경우 앱을 완전히 종료 후 재실행하거나 1:1문의를 이용해주세요.");
		dialog->setButtonType(Dialog::BUTTON_TYPE_1);
		dialog->setPositiveButtonText("확인");
		break;
	}

	case BUILD_TYPE_DATA_FETCH_FAILURE:
	{
		dialog->setTitle("정보 요청 실패");
		dialog->setMessage("서버로부터 사용자 정보를 가져오는데 실패하였습니다. 로그인을 다시 시도 합니다. 문제가 지속될 경우 앱을 완전히 종료 후 재실행하거나 1:1문의를 이용해주세요.");
		dialog->setButtonType(Dialog::BUTTON_TYPE_1);
		dialog->setPositiveButtonText("확인");
		break;
	}

	case BUILD_TYPE_UNLINK_FAILURE:
	{
		dialog->setTitle("회원탈퇴 실패");
		dialog->setMessage("알 수 없는 오류로 회원탈퇴에 실패하였습니다. 다시 로그인 한 후에 재시도 해보시길 바랍니다. 문제가 지속될 경우 앱을 완전히 종료 후 재실행하거나 1:1문의를 이용해주세요.");
		dialog->setButtonType(Dialog::BUTTON_TYPE_1);
		dialog->setPositiveButtonText("확인");
		break;
	}

	case BUILD_TYPE_INTERNAL_ERROR:
	{
		dialog->setTitle("내부 오류");
		dialog->setMessage("알 수 없는 오류가 발생했습니다. 앱을 종료합니다. 다시 실행시켜 주세요.");
		dialog->setButtonType(Dialog::BUTTON_TYPE_1);
		dialog->setPositiveButtonText("확인");
		break;
	}

	}

	return dialog;
}