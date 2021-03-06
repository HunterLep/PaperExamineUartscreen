/***********************************************
/gen auto by zuitools
***********************************************/
#ifndef __MAINACTIVITY_H__
#define __MAINACTIVITY_H__


#include "app/Activity.h"
#include "entry/EasyUIContext.h"

#include "uart/ProtocolData.h"
#include "uart/ProtocolParser.h"

#include "utils/Log.h"
#include "control/ZKDigitalClock.h"
#include "control/ZKButton.h"
#include "control/ZKCircleBar.h"
#include "control/ZKDiagram.h"
#include "control/ZKListView.h"
#include "control/ZKPointer.h"
#include "control/ZKQRCode.h"
#include "control/ZKTextView.h"
#include "control/ZKSeekBar.h"
#include "control/ZKEditText.h"
#include "control/ZKVideoView.h"
#include "window/ZKSlideWindow.h"

/*TAG:Macro宏ID*/
#define ID_MAIN_TextView6    50024
#define ID_MAIN_DebugText_17    50023
#define ID_MAIN_DebugText_16    50022
#define ID_MAIN_DebugText_15    50021
#define ID_MAIN_DebugText_14    50020
#define ID_MAIN_DebugText_13    50019
#define ID_MAIN_DebugText_12    50018
#define ID_MAIN_DebugText_11    50017
#define ID_MAIN_DebugText_10    50016
#define ID_MAIN_DebugText_9    50015
#define ID_MAIN_DebugText_8    50014
#define ID_MAIN_DebugText_7    50013
#define ID_MAIN_DebugText_6    50012
#define ID_MAIN_DebugText_5    50011
#define ID_MAIN_DebugText_4    50010
#define ID_MAIN_DebugText_3    50009
#define ID_MAIN_DebugText_2    50008
#define ID_MAIN_DebugText_1    50007
#define ID_MAIN_DebugText    50006
#define ID_MAIN_DebugWindow    110001
#define ID_MAIN_Button1    20001
#define ID_MAIN_TextView5    50005
#define ID_MAIN_EditText1    51001
#define ID_MAIN_TextView1    50001
#define ID_MAIN_Button3    20003
#define ID_MAIN_Button2    20002
#define ID_MAIN_TextView4    50004
#define ID_MAIN_TextView3    50003
#define ID_MAIN_TextView2    50002
/*TAG:Macro宏ID END*/

class mainActivity : public Activity, 
                     public ZKSeekBar::ISeekBarChangeListener, 
                     public ZKListView::IItemClickListener,
                     public ZKListView::AbsListAdapter,
                     public ZKSlideWindow::ISlideItemClickListener,
                     public EasyUIContext::ITouchListener,
                     public ZKEditText::ITextChangeListener,
                     public ZKVideoView::IVideoPlayerMessageListener
{
public:
    mainActivity();
    virtual ~mainActivity();

    /**
     * 注册定时器
     */
	void registerUserTimer(int id, int time);
	/**
	 * 取消定时器
	 */
	void unregisterUserTimer(int id);
	/**
	 * 重置定时器
	 */
	void resetUserTimer(int id, int time);

protected:
    /*TAG:PROTECTED_FUNCTION*/
    virtual const char* getAppName() const;
    virtual void onCreate();
    virtual void onClick(ZKBase *pBase);
    virtual void onResume();
    virtual void onPause();
    virtual void onIntent(const Intent *intentPtr);
    virtual bool onTimer(int id);

    virtual void onProgressChanged(ZKSeekBar *pSeekBar, int progress);

    virtual int getListItemCount(const ZKListView *pListView) const;
    virtual void obtainListItemData(ZKListView *pListView, ZKListView::ZKListItem *pListItem, int index);
    virtual void onItemClick(ZKListView *pListView, int index, int subItemIndex);

    virtual void onSlideItemClick(ZKSlideWindow *pSlideWindow, int index);

    virtual bool onTouchEvent(const MotionEvent &ev);

    virtual void onTextChanged(ZKTextView *pTextView, const string &text);

    void rigesterActivityTimer();

    virtual void onVideoPlayerMessage(ZKVideoView *pVideoView, int msg);
    void videoLoopPlayback(ZKVideoView *pVideoView, int msg, size_t callbackTabIndex);
    void startVideoLoopPlayback();
    void stopVideoLoopPlayback();
    bool parseVideoFileList(const char *pFileListPath, std::vector<string>& mediaFileList);
    int removeCharFromString(string& nString, char c);


private:
    /*TAG:PRIVATE_VARIABLE*/
    int mVideoLoopIndex;
    int mVideoLoopErrorCount;

};

#endif