#pragma once
#include "uart/ProtocolSender.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
/*
*此文件由GUI工具生成
*文件功能：用于处理用户的逻辑相应代码
*功能说明：
*========================onButtonClick_XXXX
当页面中的按键按下后系统会调用对应的函数，XXX代表GUI工具里面的[ID值]名称，
如Button1,当返回值为false的时候系统将不再处理这个按键，返回true的时候系统将会继续处理此按键。比如SYS_BACK.
*========================onSlideWindowItemClick_XXXX(int index) 
当页面中存在滑动窗口并且用户点击了滑动窗口的图标后系统会调用此函数,XXX代表GUI工具里面的[ID值]名称，
如slideWindow1;index 代表按下图标的偏移值
*========================onSeekBarChange_XXXX(int progress) 
当页面中存在滑动条并且用户改变了进度后系统会调用此函数,XXX代表GUI工具里面的[ID值]名称，
如SeekBar1;progress 代表当前的进度值
*========================ogetListItemCount_XXXX() 
当页面中存在滑动列表的时候，更新的时候系统会调用此接口获取列表的总数目,XXX代表GUI工具里面的[ID值]名称，
如List1;返回值为当前列表的总条数
*========================oobtainListItemData_XXXX(ZKListView::ZKListItem *pListItem, int index)
 当页面中存在滑动列表的时候，更新的时候系统会调用此接口获取列表当前条目下的内容信息,XXX代表GUI工具里面的[ID值]名称，
如List1;pListItem 是贴图中的单条目对象，index是列表总目的偏移量。具体见函数说明
*========================常用接口===============
*LOGD(...)  打印调试信息的接口
*mTextXXXPtr->setText("****") 在控件TextXXX上显示文字****
*mButton1Ptr->setSelected(true); 将控件mButton1设置为选中模式，图片会切换成选中图片，按钮文字会切换为选中后的颜色
*mSeekBarPtr->setProgress(12) 在控件mSeekBar上将进度调整到12
*mListView1Ptr->refreshListView() 让mListView1 重新刷新，当列表数据变化后调用
*mDashbroadView1Ptr->setTargetAngle(120) 在控件mDashbroadView1上指针显示角度调整到120度
*
* 在Eclipse编辑器中  使用 “alt + /”  快捷键可以打开智能提示
*/
static BYTE mode1[]={'M'};
static BYTE mode2[]={'S'};
static BYTE mode3[]={'C'};
UINT paper_num[10];
/**
 * 注册定时器
 * 填充数组用于注册定时器
 * 注意：id不能重复
 */
static S_ACTIVITY_TIMEER REGISTER_ACTIVITY_TIMER_TAB[] = {
	//{0,  6000}, //定时器id=0, 时间间隔6秒
	//{1,  1000},
};

/**
 * 当界面构造时触发
 */
static void onUI_init(){
    //Tips :添加 UI初始化的显示代码到这里,如:mText1Ptr->setText("123");
	usleep(10000);
}

/**
 * 当切换到该界面时触发
 */
static void onUI_intent(const Intent *intentPtr) {
    if (intentPtr != NULL) {
        //TODO
    }
}

/*
 * 当界面显示时触发
 */
static void onUI_show() {

}

/*
 * 当界面隐藏时触发
 */
static void onUI_hide() {

}

/*
 * 当界面完全退出时触发
 */
static void onUI_quit() {

}

/**
 * 串口数据回调接口
 */
char cache[18][255];
char *p[18] = {cache[0], cache[1],cache[2],cache[3],cache[4],
		cache[5],cache[6],cache[7],cache[8],cache[9],cache[10],
		cache[11],cache[12],cache[13],cache[14],cache[15],cache[16],cache[17]};
char b[20];

static void onProtocolDataUpdate(const SProtocolData &data) {
	char a[20];
	ZKTextView* debugViewList[18] = {mDebugTextPtr, mDebugText_1Ptr, mDebugText_2Ptr,
			mDebugText_3Ptr, mDebugText_4Ptr, mDebugText_5Ptr, mDebugText_6Ptr,
			mDebugText_7Ptr, mDebugText_8Ptr, mDebugText_9Ptr, mDebugText_10Ptr,
			mDebugText_11Ptr, mDebugText_12Ptr, mDebugText_13Ptr,mDebugText_14Ptr,
			mDebugText_15Ptr, mDebugText_16Ptr, mDebugText_17Ptr};
	switch(data.type) {
		case shortageError:{
			if(data.shortage==0x01)
				mTextView2Ptr->setText("短路警告！");
			else
				mTextView2Ptr->setText("电路工作正常");
			mTextView3Ptr->setText("纸张数量：--");
			mTextView4Ptr->setText("纸张状态：--");
			mTextView5Ptr->setText("校准状态：--");
			break;
		}
		case paperResult:{
			if(data.paper_exceed==0x01)
			{
				mTextView4Ptr->setText("纸张超量警告！");
				mTextView3Ptr->setText("纸张数量：--");
			}
			else {
				mTextView4Ptr->setText("纸张数正常");
				sprintf(a, "纸张数量: %d", data.paper_num);
				mTextView3Ptr->setText(a);
			}
			mTextView2Ptr->setText("电路状态：--");
			mTextView5Ptr->setText("校准状态：--");
			break;
		}
		case calibration:{
			if(data.calibration==0x00)
				mTextView5Ptr->setText("校准成功");
			else mTextView5Ptr->setText("校准失败");
			mTextView3Ptr->setText("纸张数量：--");
			mTextView4Ptr->setText("纸张状态：--");
			mTextView2Ptr->setText("电路状态：--");
			break;
		}
		case debugResult:{
			sprintf(p[0], "%s", data.debug_data);
			char *buf = p[0];
			for (int i = 0;i < 17;i ++) {
				p[i] = p[i + 1];
			}
			p[17] = buf;
			for (int i = 0;i < 18;i ++) {
				debugViewList[i]->setText(p[i]);
			}
		}
	}

}

/**
 * 定时器触发函数
 * 不建议在此函数中写耗时操作，否则将影响UI刷新
 * 参数： id
 *         当前所触发定时器的id，与注册时的id相同
 * 返回值: true
 *             继续运行当前定时器
 *         false
 *             停止运行当前定时器
 */
static bool onUI_Timer(int id){
	switch (id) {

		default:
			break;
	}
    return true;
}

/**
 * 有新的触摸事件时触发
 * 参数：ev
 *         新的触摸事件
 * 返回值：true
 *            表示该触摸事件在此被拦截，系统不再将此触摸事件传递到控件上
 *         false
 *            触摸事件将继续传递到控件上
 */
static bool onmainActivityTouchEvent(const MotionEvent &ev) {
    switch (ev.mActionStatus) {
		case MotionEvent::E_ACTION_DOWN://触摸按下
			//LOGD("时刻 = %ld 坐标  x = %d, y = %d", ev.mEventTime, ev.mX, ev.mY);
			break;
		case MotionEvent::E_ACTION_MOVE://触摸滑动
			break;
		case MotionEvent::E_ACTION_UP:  //触摸抬起
			break;
		default:
			break;
	}
	return false;
}


static void onEditTextChanged_EditText1(const std::string &text) {
    //LOGD(" onEditTextChanged_ EditText1 %s !!!\n", text.c_str());
	paper_num[0] = atoi(text.c_str());

}

static bool onButtonClick_Button1(ZKButton *pButton) {
    //LOGD(" ButtonClick Button1 !!!\n");
	sendProtocol(cmdID_MEASURE,mode1,1);
    return false;
}

static bool onButtonClick_Button2(ZKButton *pButton) {
    //LOGD(" ButtonClick Button2 !!!\n");
	sendProtocol(cmdID_SELF_CHECK,mode2,1);
    return false;
}

static bool onButtonClick_Button3(ZKButton *pButton) {
    //LOGD(" ButtonClick Button3 !!!\n");
	sendnumProtocol(cmdID_CALIBRATE_NUM,paper_num,3);
    return false;
}


