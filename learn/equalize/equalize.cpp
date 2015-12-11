//ͼ��ĻҶ�ֱ��ͼ���⻯  
//By MoreWindows (http://blog.csdn.net/MoreWindows)  
#include <opencv2/opencv.hpp>  
//#include <opencv2/legacy/compat.hpp>  
using namespace std;
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")  
void FillWhite(IplImage *pImage)
{
	cvRectangle(pImage, cvPoint(0, 0), cvPoint(pImage->width, pImage->height), CV_RGB(255, 255, 255), CV_FILLED);
}
// �����Ҷ�ͼ���ֱ��ͼ  
CvHistogram* CreateGrayImageHist(IplImage **ppImage)
{
	int nHistSize = 256;
	float fRange[] = { 0, 255 };  //�Ҷȼ��ķ�Χ    
	float *pfRanges[] = { fRange };
	CvHistogram *pcvHistogram = cvCreateHist(1, &nHistSize, CV_HIST_ARRAY, pfRanges);
	cvCalcHist(ppImage, pcvHistogram);
	return pcvHistogram;
}
// ����ֱ��ͼ����ֱ��ͼͼ��  
IplImage* CreateHisogramImage(int nImageWidth, int nScale, int nImageHeight, CvHistogram *pcvHistogram)
{
	IplImage *pHistImage = cvCreateImage(cvSize(nImageWidth * nScale, nImageHeight), IPL_DEPTH_8U, 1);
	FillWhite(pHistImage);

	//ͳ��ֱ��ͼ�е����ֱ����  
	float fMaxHistValue = 0;
	cvGetMinMaxHistValue(pcvHistogram, NULL, &fMaxHistValue, NULL, NULL);

	//�ֱ�ÿ��ֱ�����ֵ���Ƶ�ͼ��  
	int i;
	for (i = 0; i < nImageWidth; i++)
	{
		//float fHistValue = cvQueryHistValue_1D(pcvHistogram, i); //����Ϊi��ֱ�����С  
		float fHistValue = (float)cvGetReal1D(pcvHistogram->bins, i);
		int nRealHeight = cvRound((fHistValue / fMaxHistValue) * nImageHeight);  //Ҫ���Ƶĸ߶�  
		cvRectangle(pHistImage,
			cvPoint(i * nScale, nImageHeight - 1),
			cvPoint((i + 1) * nScale - 1, nImageHeight - nRealHeight),
			cvScalar(i, 0, 0, 0),
			CV_FILLED
			);
	}
	return pHistImage;
}
int main(int argc, char** argv)
{
	const char *pstrWindowsSrcTitle = "ԭͼ";
	const char *pstrWindowsGrayTitle = "�Ҷ�ͼ";
	const char *pstrWindowsHistTitle = "ֱ��ͼ";
	const char *pstrWindowsGrayEqualizeTitle = "�Ҷ�ͼ-���⻯��";
	const char *pstrWindowsHistEqualizeTitle = "ֱ��ͼ-���⻯��";

	// ���ļ��м���ԭͼ  
	IplImage *pSrcImage = cvLoadImage("picture.jpg", CV_LOAD_IMAGE_UNCHANGED);
	IplImage *pGrayImage = cvCreateImage(cvGetSize(pSrcImage), IPL_DEPTH_8U, 1);
	IplImage *pGrayEqualizeImage = cvCreateImage(cvGetSize(pSrcImage), IPL_DEPTH_8U, 1);

	// �Ҷ�ͼ  
	cvCvtColor(pSrcImage, pGrayImage, CV_BGR2GRAY);
	// ֱ��ͼͼ������  
	int nHistImageWidth = 255;
	int nHistImageHeight = 150;
	int nScale = 2;

	// �Ҷ�ֱ��ͼ��ֱ��ͼͼ��  
	CvHistogram *pcvHistogram = CreateGrayImageHist(&pGrayImage);
	IplImage *pHistImage = CreateHisogramImage(nHistImageWidth, nScale, nHistImageHeight, pcvHistogram);

	// ���⻯  
	cvEqualizeHist(pGrayImage, pGrayEqualizeImage);

	// ���⻯��ĻҶ�ֱ��ͼ��ֱ��ͼͼ��  
	CvHistogram *pcvHistogramEqualize = CreateGrayImageHist(&pGrayEqualizeImage);
	IplImage *pHistEqualizeImage = CreateHisogramImage(nHistImageWidth, nScale, nHistImageHeight, pcvHistogramEqualize);

	// ��ʾ  
	cvNamedWindow(pstrWindowsSrcTitle, CV_WINDOW_AUTOSIZE);
	cvNamedWindow(pstrWindowsGrayTitle, CV_WINDOW_AUTOSIZE);
	cvNamedWindow(pstrWindowsHistTitle, CV_WINDOW_AUTOSIZE);
	cvNamedWindow(pstrWindowsGrayEqualizeTitle, CV_WINDOW_AUTOSIZE);
	cvNamedWindow(pstrWindowsHistEqualizeTitle, CV_WINDOW_AUTOSIZE);

	cvShowImage(pstrWindowsSrcTitle, pSrcImage);
	cvShowImage(pstrWindowsGrayTitle, pGrayImage);
	cvShowImage(pstrWindowsHistTitle, pHistImage);
	cvShowImage(pstrWindowsGrayEqualizeTitle, pGrayEqualizeImage);
	cvShowImage(pstrWindowsHistEqualizeTitle, pHistEqualizeImage);

	cvWaitKey(0);

	//������Դ���롭  
	cvDestroyAllWindows();
	cvReleaseImage(&pSrcImage);
	cvReleaseImage(&pGrayImage);
	cvReleaseHist(&pcvHistogram);
	cvReleaseImage(&pHistImage);
	cvReleaseImage(&pGrayEqualizeImage);
	cvReleaseHist(&pcvHistogramEqualize);
	cvReleaseImage(&pHistEqualizeImage);
	return 0;
}