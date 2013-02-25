/************************************************************************
* Copyright(c) 2011  Yang Xian
* All rights reserved.
*
* File:	MOGExtractForeground.cpp
* Brief: ���ڻ�ϸ�˹ģ�͵�ǰ�����
* Version: 1.0
* Author: Yang Xian
* Email: xyang2011@sinano.ac.cn
* Date:	2011/11/19
* History:
************************************************************************/
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/video.hpp>

#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat frame; 
	Mat foreground;	// ǰ��ͼƬ
	VideoCapture capture("bike.avi");

	if (!capture.isOpened())
	{
		return 0;
	}

	namedWindow("Extracted Foreground");
	namedWindow("Source Video");
	// ��ϸ�˹����
	BackgroundSubtractorMOG mog;
	bool stop(false);
	while (!stop)
	{
		if (!capture.read(frame))
		{
			break;
		}
		// ���±���ͼƬ�������ǰ��
		mog(frame, foreground, 0.01);
		// �����ǰ��ͼƬ������2ֵͼƬ��Ҫ����һ����ʾ  
		threshold(foreground, foreground, 128, 255, THRESH_BINARY_INV);
		// show foreground
		imshow("Extracted Foreground", foreground);
		imshow("Source Video", frame);
		if (waitKey(30) == 'q')
		{
			stop = true;
		}
	}
}
