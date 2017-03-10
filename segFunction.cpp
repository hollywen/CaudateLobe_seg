#include "SegFunction.h"


/**************************************************************************************/
// 开发单位：    华中科技大学医学图像信息研究中心
// 主要开发人员：金人超 许立君 计长兵
// 主要测试人员：
// E-mail：  jrc@hust.edu.cn
// QQ:        281381994
/****************************************************************************************/


namespace CbibSeg{

SegFunction::SegFunction(void)
{

	init();
}
void SegFunction::init()
{

	gFileName = "E:/Case/ChenCongmei/";
	// pretreatment
	iContrastFlag=70;//造影剂使用标记
	iMaxIm=100;
	iCurdeHigh=1150;//初始阈值上界
	iCurdeLow=1000;//初始阈值下界
	iCuredeRange=iCurdeHigh-iCurdeLow;//上下界的差
	iGuassian2DSize=31;//2D高斯模板大小；
	iGuassian2DGamga=5;//2D高斯gama值；
	iLocalLowerBound=350;//局部最小值下界
	iLocalPage=80;//局部最小值page值。
	iMinDis=10;

	//预处理用参数
	iGain=iCurdeLow;
	fNorm=3.0f;//分辨率，分辨率小于fpsace的时候，为fspaeZ;

	//gmac辅助用参数
	fStdGbParm=3.0f;
	fBataParm=8000;
	fThetaParm=60.0f;
	fLambdaParm=0.01f;
	fDtParm=8.0f;
	fStdPwmParm=999.0f;
	fNgParm=6.0f;
	iNbIterUpdateParm=30;
	iIterationCountParm=300;
	fThreU=0.2f;
	fReginGrowParm=0.0005f;

	iCuredeRange=iCurdeHigh-iCurdeLow;

}

void SegFunction::showParm()
{
	printf("iContrastFlag %d\n",iContrastFlag);
	printf("iMaxIm %d\n",iMaxIm);
	printf("iCurdeHigh %d\n",iCurdeHigh);
	printf("iCurdeLow %d\n",iCurdeLow);
	printf("iCuredeRange %d\n",iCuredeRange);
	printf("iGuassian2DSize %d\n",iGuassian2DSize);
	printf("iGuassian2DGamga %.4f\n",iGuassian2DGamga);
	printf("iLocalLowerBound %d\n",iLocalLowerBound);
	printf("iLocalPage %d\n",iLocalPage);
	printf("iMinDis %d\n",iMinDis);
	printf("iGain %d\n",iGain);
	printf("fNorm %.4f\n",fNorm);
	printf("fStdGbParm %.4f\n",fStdGbParm);
	printf("fBataParm %.4f\n",fBataParm);
	printf("fThetaParm %.4f\n",fThetaParm);
	printf("fLambdaParm %.4f\n",fLambdaParm);
	printf("fDtParm %.4f\n",fDtParm);
	printf("fStdPwmParm %.4f\n",fStdPwmParm);
	printf("fNgParm %.4f\n",fNgParm);
	printf("iNbIterUpdateParm %d\n",iNbIterUpdateParm);
	printf("iIterationCountParm %d\n",iIterationCountParm);
	printf("fThreU %.4f\n",fThreU);
	printf("fReginGrowParm %.4f\n",fReginGrowParm);
}
bool SegFunction::initParm()
{
	//读初始化配置文件。
	FILE *fConfig;

	errno_t err=fopen_s(&fConfig,"parm.config","r");
	if(err!=0) 
	{ 
		printf("parm.config is not exist, system will use default parameters.\n"); 
		return false;
	}
	else{ 
	//固定的配置文件
	fscanf_s(fConfig,"%d",&iContrastFlag);
	fscanf_s(fConfig,"%d",&iMaxIm);
	fscanf_s(fConfig,"%d",&iCurdeHigh);
	fscanf_s(fConfig,"%d",&iCurdeLow);
	fscanf_s(fConfig,"%d",&iCuredeRange);
	fscanf_s(fConfig,"%d",&iGuassian2DSize);
	fscanf_s(fConfig,"%f",&iGuassian2DGamga);
	fscanf_s(fConfig,"%d",&iLocalLowerBound);
	fscanf_s(fConfig,"%d",&iLocalPage);
	fscanf_s(fConfig,"%d",&iMinDis);
	fscanf_s(fConfig,"%d",&iGain);
	fscanf_s(fConfig,"%f",&fNorm);
	fscanf_s(fConfig,"%f",&fStdGbParm);
	fscanf_s(fConfig,"%f",&fBataParm);
	fscanf_s(fConfig,"%f",&fThetaParm);
	fscanf_s(fConfig,"%f",&fLambdaParm);
	fscanf_s(fConfig,"%f",&fDtParm);
	fscanf_s(fConfig,"%f",&fStdPwmParm);
	fscanf_s(fConfig,"%f",&fNgParm);
	fscanf_s(fConfig,"%d",&iNbIterUpdateParm);
	fscanf_s(fConfig,"%d",&iIterationCountParm);
	fscanf_s(fConfig,"%f",&fThreU);
	fscanf_s(fConfig,"%f",&fReginGrowParm);
	
	}
	fclose(fConfig);
	iCuredeRange=iCurdeHigh-iCurdeLow;
	iGain=iCurdeLow;
	return true;
}
bool SegFunction::initParm(char * filename)
{
	FILE *fConfig;

	errno_t err=fopen_s(&fConfig,filename,"r");
	if(err!=0) 
	{ 
		printf("parm.config is not exist, system will use default parameters.\n"); 
		return false;
	}
	else{ 
		//固定的配置文件
		fscanf_s(fConfig,"%d",&iContrastFlag);
		fscanf_s(fConfig,"%d",&iMaxIm);
		fscanf_s(fConfig,"%d",&iCurdeHigh);
		fscanf_s(fConfig,"%d",&iCurdeLow);
		fscanf_s(fConfig,"%d",&iCuredeRange);
		fscanf_s(fConfig,"%d",&iGuassian2DSize);
		fscanf_s(fConfig,"%f",&iGuassian2DGamga);
		fscanf_s(fConfig,"%d",&iLocalLowerBound);
		fscanf_s(fConfig,"%d",&iLocalPage);
		fscanf_s(fConfig,"%d",&iMinDis);
		fscanf_s(fConfig,"%d",&iGain);
		fscanf_s(fConfig,"%f",&fNorm);
		fscanf_s(fConfig,"%f",&fStdGbParm);
		fscanf_s(fConfig,"%f",&fBataParm);
		fscanf_s(fConfig,"%f",&fThetaParm);
		fscanf_s(fConfig,"%f",&fLambdaParm);
		fscanf_s(fConfig,"%f",&fDtParm);
		fscanf_s(fConfig,"%f",&fStdPwmParm);
		fscanf_s(fConfig,"%f",&fNgParm);
		fscanf_s(fConfig,"%d",&iNbIterUpdateParm);
		fscanf_s(fConfig,"%d",&iIterationCountParm);
		fscanf_s(fConfig,"%f",&fThreU);
		fscanf_s(fConfig,"%f",&fReginGrowParm);
		fclose(fConfig);
	}
		iCuredeRange=iCurdeHigh-iCurdeLow;
		iGain=iCurdeLow;
		return true;
fclose(fConfig);
}
SegFunction::~SegFunction(void)
{   /*delete[] this->UIterationtemp1;
	delete[] this->UIterationtemp2;
	delete[] this->UIterationtemp3;
	delete[] this->UIterationtemp4;
	delete[] this->UIterationtemp5;*/
}


//需要提交的子函数
	//规定必须为薄层。层厚<=3.0
	/************************************************************************/
	/* 
	pData_Base:需要分割的原始数据

	iDimension：维数
	            iDimension[0]--x维数
				iDimension[1]--y维数
				iDimension[2]--z维数
				 
	fSpace:分辨率
	       fSpace[0]--x分辨率
	       fSpace[1]--y分辨率
	       fSpace[2]--z分辨率

    bMultiThread：是否使用多线程，flase为不使用多线程、true 为使用多线程，默认值为true

	otherparm:一些其他需要用的参数，该版本还未添加。

	pAllMask：最后得到的掩膜,按照宏定义，label=1为非肝部分，label=2为肝脏部分。

	bHaveVessel：掩膜中是否有血管，flase为没有血管，true 为有血管。默认值为flase。
	*/
	/************************************************************************/
bool SegFunction::liversegment(short *pData_Base,const int *iDimension, const float *fSpace,const bool bMultiThread=false,int *otherparm=NULL,char *pAllMask=NULL,bool *bHaveVessel=false)
{
	initParm();
	if(pData_Base==NULL||iDimension==NULL||fSpace==NULL) return false;

	*bHaveVessel=false;
	this->bHaveVessel=false;
	this->bMultiThread=bMultiThread;
	this->otherparm=otherparm;

	showParm();
	//用于gmac计时
	time_t timeBegin, timeEnd; 

	iDimX=iDimension[0];	//设置x轴长度width
	iDimY=iDimension[1];	//设置y轴长度height
	iDimZ=iDimension[2];	//设置z轴长度depth
	tempNum=iDimX*iDimY*iDimZ; //设置缓存区长度。
	
	fSpaceX=fSpace[0];	//设置x轴分辨率
	fSpaceY=fSpace[1];  //设置y轴分辨率
	fSpaceZ=fSpace[2];  //设置z轴分辨率
	
	pData_temp = pData_Base;  //初始化ct值数据缓存大小
	pMask_temp = pAllMask;  //初始化mask数据缓存大小


	UIterationtemp1=new float[iDimX*iDimY*iDimZ];
	UIterationtemp2=new float[iDimX*iDimY*iDimZ];
	UIterationtemp3=new float[iDimX*iDimY*iDimZ];
	UIterationtemp4=new float[iDimX*iDimY*iDimZ];
	UIterationtemp5=new float[iDimX*iDimY*iDimZ];


	memset(pMask_temp,0,tempNum*sizeof(char));   //赋初值

	printf("\n iDimX: %d iDimY %d iDimZ %d",iDimX,iDimY,iDimZ);
	printf("\n fSpaceX: %.4f fSpaceY %.4f fSpaceZ %.4f",fSpaceX,fSpaceY,fSpaceZ);

	//找肝脏的位置
    find_liverLocation();

	//测试使用

	printf("\n  iStart: %d iEnd %d\n ",iStart,iEnd);

	//当实际分辨率小于控制分辨率时采用实际分辨率
	if(fNorm<fSpaceZ)fNorm=fSpaceZ;	

	//预处理
 	pre_processing(iGain,true,iStart,iEnd,true,fNorm);

	//gamc
	timeBegin = time(NULL);  
	gmac3D();//返回了U
	timeEnd = time(NULL);  
	printf("\ngmac time :%d\n", int(timeEnd - timeBegin));  

	//最后的U
	//unsigned char *imgBufSet;
	//imgBufSet=new unsigned char[iDimX*iDimY*iDimZ];
	//for(int i=0;i<iDimX*iDimY*iDimZ;i++)
	//{
	//	imgBufSet[i]=static_cast<unsigned char>(u[i]*255);
	//}
	//dumpBmp("FinalU_BMP",imgBufSet,iDimX,iDimY,iDimZ,8);
	//delete[] imgBufSet;
	
	//后期处理
// 
	tempDim[0]=iDimX;
	tempDim[1]=iDimY;
	tempDim[2]=iDimZ;
	temp=new float[iDimX*iDimY*iDimZ];
	memcpy(temp,u,iDimX*iDimY*iDimZ*sizeof(float));
	
	post_processing(iDimension,false,true,iStart,iEnd);
	
	ippsFree(u);
	ippsFree(v);
	//writeData(pMask_temp,"F://3//mask.raw",iDimension);
	//调用肝脏分段程序
	int a=iDimension[0];
	int b=iDimension[1];
	int c=iDimension[2];
	int len8=iDimension[0]*iDimension[1]*iDimension[2];
	char *mask8=new char[len8];  //肝脏八段掩膜
	memset(mask8,0,len8*sizeof(char));

	//****************根据中心线文件进行分段
	//centerlineName="F://CentreLine2//HIU16//11_YuHao//11_YuHao.txt";
	//seg_mask_8(pMask_temp,centerlineName,mask8,iDimension); //根据中心线文件分割肝
	//**********************************

	//*********************************根据手工选取的血管点进行分段
	//int vein[3]={0};
	int veinR[3]={0};
	int veinM[3]={0};
	//int portal[3]={0};
	int portalL[3]={0};
	int portalLineL=0;
	int portalLineR=0;
	//centerlineName = (gFileName + "vesselPoint.txt").c_str();

	// 输出肝部分Mask
	//writeData(pAllMask,gFileName + "mask.raw",iDimension);

	FILE *fp;
	fp=fopen((gFileName+"vesselPoint.txt").c_str(),"r");
	//char endchar;
	//while((endchar=(char)fgetc(fp))!=EOF)
	//{
	  fscanf(fp,"%d%d%d",&veinPoint[0],&veinPoint[1],&veinPoint[2]);
	  fscanf(fp,"%d%d%d",&veinR[0],&veinR[1],&veinR[2]);
	  fscanf(fp,"%d%d%d",&veinM[0],&veinM[1],&veinM[2]);
	  fscanf(fp,"%d%d%d",&portalPoint[0],&portalPoint[1],&portalPoint[2]);
	  fscanf(fp,"%d%d%d",&portalL[0],&portalL[1],&portalL[2]);
	  fscanf(fp,"%d",&portalLineL);
	  fscanf(fp,"%d",&portalLineR);
	//}
	fclose(fp);
	seg_mask_8(pAllMask,veinPoint,veinR,veinM,portalPoint,portalL,portalLineL,portalLineR,mask8,iDimension);
	//***********************************
	//fwrite(temp,sizeof(unsigned char),len,fp);




	// 输出肝七段分割结果
	//writeData(mask8,gFileName + "seg7_mask.raw",iDimension);
	//rotate(mask8,iDimension,veinPoint,portalPoint,portalL);
	



	
	// 肝八段自动分割运行时间
	time_t begin,end;
	int timeCost;
	begin = time(NULL);


	int *iTranDim = new int[3];
	int *iTranOriginal = new int[3];
	calculateTranDim(iTranOriginal, iTranDim, mask8, iDimension);  //计算平移变换后的大小


	int iTranLength = iTranDim[0] * iTranDim[1] * iTranDim[2];    // 平移变换后图像的大小
	//int iTranSizeXY = iTranDim[0] * iTranDim[1];                  // 平移变换后图像的页面大小(一层)
	// 存储平移变换之后的mask和raw
	char *pTranMask = new char[iTranLength];
	short *pTranRaw = new short[iTranLength];


	translateTran(iTranOriginal, iTranDim, pTranRaw, pTranMask, pData_Base, mask8, iDimension); //平移变换函数 使用pData_Base输出变换后的Raw（中间结果） 方便测试使用
	//pTranMask = translateTran(iTranOriginal, iTranDim, mask8, iDimension); // 平移变换函数不输出中间结果Raw

	
	char *pTranMask_temp = new char[iTranLength];
	memcpy(pTranMask_temp, pTranMask, sizeof(char)*iTranLength);

	seg_CaudateLobe(pTranMask, iTranOriginal, iTranDim); // 分割肝尾页

	char *pMask = NULL;
	pMask = translateTranReverse(iTranOriginal, iTranDim, pTranMask, mask8, iDimension); //平移逆变换函数
	writeData(pMask,gFileName + "pMask.raw",iDimension);
	end = time(NULL);
	timeCost = end - begin; 



	// 肝八段手动分割运行时间
	time_t beginManual,endManual;
	int timeCostManual;
	beginManual = time(NULL);
	//*******************根据自动分割的结果进行手动修改  补割需要调用不同的函数
	 seg_CaudateLobe_manual_mend(pTranMask_temp,iTranOriginal,iTranDim);
	 //seg_CaudateLobe_manual_cut(pTranMask_temp,iTranOriginal,iTranDim);
	//*********************

	
	 /*手工动作主要分两种，一种是补，一种是割
	   并且位置也分为两处，第一处是尾叶与2、3段之间连接部分，第二处是尾叶与6、7段连接的部分
	   第一处直接保存手工分割肝尾叶结果即可
	   第二处在割的时候，需要将割掉的部分还给6、7段
	 */
	
	bool bCutFlag = false;
	for(int i=0;i<iTranLength;i++)
	 {
	   if(pTranMask[i]==LIVER_8SEGMENT_PART9 && pTranMask_temp[i]!=LIVER_8SEGMENT_PART9)
	   {
		   pTranMask_temp[i]=LIVER_8SEGMENT_PART7;
		   bCutFlag = true;
	   }
	 }
	//memcpy(pTranMask, pTranMask_temp, sizeof(char)*iTranLength);

	char *pMaskManual = NULL;
	pMaskManual = translateTranReverse(iTranOriginal, iTranDim, pTranMask_temp, mask8, iDimension); //平移逆变换函数


	//****************在第二处分割，将割掉的部分还给6、7段，注意坐标是变换后的坐标
	if(bCutFlag)
	{
		seg_mask_8_3(portalLineR, pMaskManual, iDimension);
	}
	
	 //*****************
	writeData(pMask,gFileName + "pMaskManual.raw",iDimension);
	endManual = time(NULL);
	timeCostManual = endManual - beginManual; 

	

	memcpy(pAllMask, pMaskManual, len8*sizeof(char));
	delete[]mask8;
	return true;
}

void SegFunction::getTemp(float *temp,int &startpage,int &endPage,int *dim)
{
	    dim[0]=tempDim[0];
 		dim[1]=tempDim[1];
		dim[2]=tempDim[2];
		startpage=this->iStart;
		endPage=this->iEnd;
 		memcpy(temp,this->temp,dim[0]*dim[1]*dim[2]*sizeof(float));
 		delete[] this->temp;
		/*temp=this->temp;*/
}

void SegFunction::getGbTemp(float *GbTemp,int &Gbstartpage,int &GbendPage,int *Gbdim)
{
	Gbdim[0]=tempDim[0];
	Gbdim[1]=tempDim[1];
	Gbdim[2]=tempDim[2];
	Gbstartpage=this->iStart;
	GbendPage=this->iEnd;
	memcpy(GbTemp,this->Gbtemp,Gbdim[0]*Gbdim[1]*Gbdim[2]*sizeof(float));
	delete[] this->Gbtemp;
}

void SegFunction::getUIterTemp(float *UIterTemp1,float *UIterTemp2,float *UIterTemp3,float *UIterTemp4,float *UIterTemp5,int &UIterstartpage,int &UIterendPage,int *UIterdim)
{
	UIterdim[0]=tempDim[0];
	UIterdim[1]=tempDim[1];
	UIterdim[2]=tempDim[2];
	UIterstartpage=this->iStart;
	UIterendPage=this->iEnd;
memcpy(UIterTemp1,this->UIterationtemp1,UIterdim[0]*UIterdim[1]*UIterdim[2]*sizeof(float));		 
memcpy(UIterTemp2,this->UIterationtemp2,UIterdim[0]*UIterdim[1]*UIterdim[2]*sizeof(float));
memcpy(UIterTemp3,this->UIterationtemp3,UIterdim[0]*UIterdim[1]*UIterdim[2]*sizeof(float));     
memcpy(UIterTemp4,this->UIterationtemp4,UIterdim[0]*UIterdim[1]*UIterdim[2]*sizeof(float));	    
memcpy(UIterTemp5,this->UIterationtemp5,UIterdim[0]*UIterdim[1]*UIterdim[2]*sizeof(float));
	delete[]this->UIterationtemp1;
	delete[]this->UIterationtemp2;
	delete[]this->UIterationtemp3;
	delete[]this->UIterationtemp4;
	delete[]this->UIterationtemp5;

}





void SegFunction::find_liverLocation()
{
	//找到肝的特征值点
	//找到肝的特征值CT，所在位置。
	//取最大最小值。

	float *H;
	H=new float[iDimZ*iCuredeRange];
	memset(H,0,iDimZ*iCuredeRange*sizeof(float));
	for(int i=0;i<iDimZ;i++){
		for(int j=0;j<iDimY;j++){
			for(int k=0;k<iDimX;k++){
				if(k<iDimY-1-j+20/fSpaceX&&pData_temp[i*iDimX*iDimY+j*iDimX+k]>=iCurdeLow&&pData_temp[i*iDimX*iDimY+j*iDimX+k]<iCurdeHigh)
				{
					H[i*iCuredeRange+(pData_temp[i*iDimX*iDimY+j*iDimX+k]-iCurdeLow)]+=(fSpaceX*fSpaceY);
				}
			}
		}
	}

	//高斯平滑
	float *sH;
	sH=new float[iDimZ*iCuredeRange];
	Gaussian_2D(sH,iCuredeRange,iDimZ,iGuassian2DSize,iGuassian2DGamga,H);
// 	printf("\nsH:\n");
// 	for(int i=0;i<iDimZ;i++)
// 	{
// 		for(int j=0;j<iCuredeRange;j++)
// 		{
// 			printf("%.8f ",sH[(iDimZ-1-i)*iCuredeRange+j]);
// 		}
// 		printf("\n");
// 	}
 //找ct值最大的z轴坐标
	int zmid=0;
	iLiverCT=0;

	int m=0;
	float ma=0.0;
	for(int i=0;i<iDimZ;i++){
		for(int j=0;j<iCuredeRange;j++){
			if(sH[m]>ma){
				ma=sH[m];
				zmid=i;
				iLiverCT=j;
			}
		    m++;
		}
	}

	printf("SH max=sH[%d,%d]: %f\n",iLiverCT,zmid,ma);

	//if(ma>iLocalLowerBound)iLocalLowerBound=(int)ma;

// 	unsigned char *img;
//  	img=new unsigned char[iDimZ*iCuredeRange];
//  	for(int i=0;i<iDimZ*iCuredeRange;i++)
//  	{
//  		//if(sH[i]<iLocalLowerBound)
//  		//	img[i]=0;
//  		//else{
//  		img[i]=static_cast<unsigned char>(sH[i]*255/ma);
//  		//}
//  		
//  	}
// 
//  	saveBmp("SH.bmp",img,iCuredeRange,iDimZ,8);
//  	delete[] img;

	//找局部最大值
	//倒着找！！！！
	int* xIn=new int[iDimZ*iCuredeRange];
	int* yIn=new int[iDimZ*iCuredeRange];
	int pointNum=0;
	localMaximun(sH,iCuredeRange,iDimZ,xIn,yIn,pointNum);
//	localMaximun(sH,iDimZ,iCuredeRange,xIn,yIn,pointNum);
	printf("iLocalLowerBound: %d\n",iLocalLowerBound);
	for(int i=pointNum-1;i>=0;i--)
	{
		printf("CT: %d,Z: %d, SH: %f\n",xIn[i],yIn[i],sH[yIn[i]*iCuredeRange+xIn[i]]);
		if(sH[yIn[i]*iCuredeRange+xIn[i]]>iLocalLowerBound)
		{
			if(!(zmid>yIn[i]&&ma>sH[yIn[i]*iCuredeRange+xIn[i]]))
			{
				iLiverCT=xIn[i];
				zmid=yIn[i];
			}
			/*		printf("IN\n")*/;
			break;
		}
	}

	printf("zmid=%d iLiverCT+iCurdeLow=%d\n",zmid,iLiverCT+iCurdeLow);

	//if(abs(zmid-iDimZ/2)>abs(zmid1-iDimZ/2))
	//	zmid=zmid1;
	printf("final : zmid=%d iLiverCT=%d\n",zmid,iLiverCT);

	delete xIn;
	delete yIn;
	delete H;
	delete sH;
	iStart=0,iEnd=iDimZ-1;

	//得出肝的起始层和终止层
	printf("\n%f\n",iLocalPage/fSpaceZ);
// 	if(zmid-iLocalPage/fSpaceZ>iStart)
// 		iStart=int(zmid-iLocalPage/fSpaceZ);
// 	if(zmid+2.0f*iLocalPage/fSpaceZ<iEnd)
// 		iEnd=int (zmid+2.0f*iLocalPage/fSpaceZ);
// 
// 	printf("start: %d,end :%d",iDimZ-iEnd-1,iDimZ-iStart-1);

	if(int(zmid+iLocalPage/fSpaceZ)<iEnd)
		iEnd=int(zmid+iLocalPage/fSpaceZ+0.5);
	if(int(zmid-2.0*iLocalPage/fSpaceZ)>iStart)
		iStart=int(zmid-2.0*iLocalPage/fSpaceZ+0.5);

	printf("start: %d,end :%d",iStart,iEnd);


}

void SegFunction::pre_processing(int iGain,bool bCut,int iStart,int iEnd,bool bInterpolation=true,float fNorm=1.0)
{
	/************************************************************************/
	/*
	函数进行预处理操作

	pData_base:原始数据
    iGain：对原始数据需要做的减益值
	
	bCut：截取层标志，true为需要截取，flase为不需要截取
	iStart：起始层号
	iEnd：终止层号

	bInterpolation:插值处理标志，ture为需要插值，flase不需要插值。默认值为true.
	fNorm：插值比例。默认值为1.0
	*/
	/************************************************************************/
	
	//去除非肝页面
	if(bCut==true)
	{
		cut_page(iStart,iEnd);
	}

	//插值
	
	if(bInterpolation==true)
	{
		interpolation(fNorm);
	}	
	
	//对原始数据进行阈值处理。
	//pData_temp的值落在[0，iMaxIm-1]
	pre_threshold(iGain,iLiverCT); 
	
}
void SegFunction::gmac3D()
{
	/************************************************************************/
	/*
	gmac操作，得到用于后期处理的u。
	*/
	/************************************************************************/
	
	 int Ng;
	 int volumnSize;
	 float *matrix;
	 
	 //初始化参数
	 std_Gb=fStdGbParm/fNorm;
	 beta=float(fBataParm/(iMaxIm*iMaxIm)/fNorm);
	 theta=float(1.0/fThetaParm);
	 lambda=float(1.0/theta*fLambdaParm);
	 dt=float(1.0/fDtParm);
	 std_pwm=fStdPwmParm;
	 NbIterUpdate=iNbIterUpdateParm;
	 Ng=static_cast<int>(ceil(fNgParm*std_Gb))+1;

	volumnSize=iDimX*iDimY*iDimZ;

	sMatrix=ippsMalloc_32f(volumnSize);
	dx=ippsMalloc_32f(volumnSize);
	dy=ippsMalloc_32f(volumnSize);
	dz=ippsMalloc_32f(volumnSize);
	gb=ippsMalloc_32f(volumnSize);
	NormGrad=ippsMalloc_32f(volumnSize);
	u=ippsMalloc_32f(volumnSize);
	v=ippsMalloc_32f(volumnSize);
	regionTermIn=ippsMalloc_32f(volumnSize);
	regionTermOut=ippsMalloc_32f(volumnSize);
	RegionTerm=ippsMalloc_32f(volumnSize);
	pxu=ippsMalloc_32f(volumnSize);
	pyu=ippsMalloc_32f(volumnSize);
	pzu=ippsMalloc_32f(volumnSize);
	term=ippsMalloc_32f(volumnSize);
	termx=ippsMalloc_32f(volumnSize);
	termy=ippsMalloc_32f(volumnSize);
	termz=ippsMalloc_32f(volumnSize);
	divp=ippsMalloc_32f(volumnSize);
	HistIn=ippsMalloc_32s(iMaxIm);
	HistOut=ippsMalloc_32s(iMaxIm);
	result=ippsMalloc_32f(512);
	PdfIn=ippsMalloc_32f(iMaxIm);
	PdfOut=ippsMalloc_32f(iMaxIm);
	Gb=ippsMalloc_32f(volumnSize);
    matrix=ippsMalloc_32f(volumnSize);
	/*Gbtemp=ippsMalloc_32f(volumnSize);;*///保存gmac中Gb的值

	//将原始数据转换成float型，并赋值给matrix。
	for (int i=0;i<volumnSize;i++)
	{
		matrix[i]=float(pData_temp[i]);
	}
//	printf("将原始数据转换成float型，并赋值给matrix \n");
// 	for(int k=48;k<=52;k++)
// 	{for(int i=0;i<iDimX;i++)
// 	{
// 		for(int j=0;j<iDimY;j++)
// 		{
// 			printf("%.8f ",matrix[k*iDimX*iDimY+i*iDimX+j]);
// 		}
// 		printf("\n");
// 	}
// 	printf("\n");
//     }
// 	unsigned char *imgBufSet;
// 	imgBufSet=new unsigned char[iDimX*iDimY*iDimZ];
// 	for(int i=0;i<iDimX*iDimY*iDimZ;i++)
// 	{
// 		imgBufSet[i]=static_cast<unsigned char>(matrix[i]*255/(iMaxIm-1));
// 	}
// 	dumpBmp("matrix_BMP",imgBufSet,iDimX,iDimY,iDimZ,8);
// 	delete[] imgBufSet;

	//高斯滤波 
	//对图像进行高斯滤波，平滑。
	printf("Gaussian_3D Ng=%d std_Gb=%f\n",Ng,std_Gb);
	Gaussian_3D(sMatrix,Ng,std_Gb,matrix);
//	writeRaw("sMatrix.raw","sMatrix.info",sMatrix,iDimX,iDimY,iDimZ);
// 	printf("对图像进行高斯滤波，平滑 \n");
// 	for(int i=0;i<iDimX;i++)
// 	{
// 		for(int j=0;j<iDimY;j++)
// 		{
// 			printf("%.8f ",sMatrix[50*iDimX*iDimY+i*iDimX+j]);
// 		}
// 		printf("\n");
// 	}
	//计算边缘侦查函数
	ComputeGb(sMatrix,iDimX,iDimY,iDimZ,Gb,NormGrad);
// 	printf("计算边缘侦查函数 \n");
//  	for(int i=0;i<iDimX;i++)
//  	{
//  		for(int j=0;j<iDimY;j++)
//  		{
//  			printf("%.8f ",Gb[50*iDimX*iDimY+i*iDimX+j]);
//  		}
//  		printf("\n");
//  	}
unsigned char *	imgBufSet=new unsigned char[iDimX*iDimY*iDimZ];
 	for(int i=0;i<iDimX*iDimY*iDimZ;i++)
 	{
 		imgBufSet[i]=static_cast<unsigned char>(Gb[i]*255);
 	}
 	dumpBmp("GB_BMP",imgBufSet,iDimX,iDimY,iDimZ,8);
	Gbtemp=new float[iDimX*iDimY*iDimZ];
	memset(Gbtemp,0,iDimX*iDimY*iDimZ*sizeof(float));
    memcpy(Gbtemp,Gb,sizeof(float)*iDimX*iDimY*iDimZ);
 	delete[] imgBufSet;

	//初始化VU
	InitUV(matrix,u,v);
	tempDim[0]=iDimX;
	tempDim[1]=iDimY;
	tempDim[2]=iDimZ;

// 	temp=new float[iDimX*iDimY*iDimZ];
// 	//float *sTemp=new float[iDimX*iDimY*iDimZ];
// 	//memcpy(sTemp,u,iDimX*iDimY*iDimZ*sizeof(float));
// 	//Gaussian_3D(temp,Ng,std_Gb,sTemp);
// 	//delete[] sTemp;
// 	memcpy(temp,u,iDimX*iDimY*iDimZ*sizeof(float));
// 
// 	imgBufSet=new unsigned char[iDimX*iDimY*iDimZ];
// 	for(int i=0;i<iDimX*iDimY*iDimZ;i++)
// 	{
// 		imgBufSet[i]=static_cast<unsigned char>(u[i]*255);
// 	}
// 	dumpBmp("InitUV_BMP",imgBufSet,iDimX,iDimY,iDimZ,8);
// 	delete[] imgBufSet;


	//迭代
	iterationCount=iIterationCountParm;
// 	int depth=iDimZ;
// 	int height=iDimY;
// 	int width=iDimX;
	for (int iter=0;iter<iterationCount;iter++)
	{
		//更新u
		//printf("updateInterval:%d\n",iter);
		Backwardx(pxu,dx,iDimX,iDimY,iDimZ);
		Backwardy(pyu,dy,iDimX,iDimY,iDimZ);
		Backwardz(pzu,dz,iDimX,iDimY,iDimZ);

         //#pragma ivdep
		for(int i=0;i<volumnSize;i++)
		{
			divp[i]=dx[i]+dy[i]+dz[i];
			term[i]=divp[i]-v[i]/theta;
		}

		Forwardx(term,termx,iDimX,iDimY,iDimZ);
		Forwardy(term,termy,iDimX,iDimY,iDimZ);
		Forwardz(term,termz,iDimX,iDimY,iDimZ);

	
		float *denom=term;
/*		float minValue=999.0, maxValue=0.0;*/
		for(int i=0;i<volumnSize;i++)
		{
			denom[i]=sqrt(termx[i]*termx[i]+termy[i]*termy[i]+termz[i]*termz[i]);
			denom[i]=Gb[i]+dt*denom[i];

			pxu[i]=Gb[i]*(pxu[i]+dt*termx[i])/denom[i];
			pyu[i]=Gb[i]*(pyu[i]+dt*termy[i])/denom[i];
			pzu[i]=Gb[i]*(pzu[i]+dt*termz[i])/denom[i];

			u[i]=v[i]-theta*divp[i];

			if(u[i]<0)u[i]=0;
 			if(u[i]>1)u[i]=1;
 
		}

	
		updateInterval=iNbIterUpdateParm;
		if(iter<1 || (iter+1) % updateInterval==0)
		{

			//  qDebug("updateInterval:%d",iter);
			int NbPtIn=0;
			int NbPtOut=0;
			memset(HistIn,0,sizeof(int)*iMaxIm);
			memset(HistOut,0,sizeof(int)*iMaxIm);
			int im;
		
	int m=0;
//	#pragma parallel
	for (int k = 0; k < iDimZ; k++){
	    for (int j = 0; j < iDimY; j++){
	        for (int i = 0; i < iDimX; i++){
				if(i < iDimY-1-j+30/fNorm){
					if(u[m]<0.5){
						NbPtOut++;
						im=pData_temp[m];
						if(im>=iMaxIm)im=iMaxIm-1;
						HistOut[im]++;
					}else{
						NbPtIn++;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              
						im=pData_temp[m];
						if(im>=iMaxIm)im=iMaxIm-1;
						HistIn[im]++;
					}
				}
				m++;
			}
		}
	}


//#pragma ivdep
			for(int i=0;i<iMaxIm;i++)
			{
				//qDebug("H: %f",H[i]);
				PdfIn[i]=float(HistIn[i])/float(NbPtIn);
				PdfOut[i]=float(HistOut[i])/float(NbPtOut);
			}
			
			int ct;
			for(int i=0; i<volumnSize;i++){
					ct=pData_temp[i];
					if(ct<0||ct>iMaxIm){
					/*	printf("ct=%d iMaxIm=%d\n",ct, iMaxIm);*/
						ct=0;
					}
					regionTermIn[i]=PdfIn[ct];
					regionTermOut[i]=PdfOut[ct];
			}

//		float minValue=999.0, maxValue=0.0;
//		float minValue1=999.0, maxValue1=0.0;

//#pragma ivdep
			for (int i=0;i<volumnSize;i++)
			{
				RegionTerm[i] = regionTermIn[i] - regionTermOut[i];

  			//if(RegionTerm[i]>maxValue)maxValue=RegionTerm[i];
  			//if(RegionTerm[i]<minValue)minValue=RegionTerm[i];
  			//if(theta*divp[i]>maxValue1)maxValue1=theta*divp[i];
  			//if(theta*divp[i]<minValue1)minValue1=theta*divp[i];
			}
//		printf("theta*divp:min=%f max=%f    RegionTerm: min=%f max=%f\n", minValue1,maxValue1,lambda * theta *minValue, lambda * theta *maxValue);

		}


		//更新v
		for (int i = 0; i < volumnSize; i++)
		{
			v[i] = u[i] + lambda * theta * RegionTerm[i];

			if (v[i] < 0.0 )
				v[i] = 0.0;

			if (v[i] > 1.0 )
				v[i] = 1.0;
		}

// 		char path[20];
// 		if(iter%50==0){
// 			imgBufSet=new unsigned char[iDimX*iDimY*iDimZ];
// 			for(int i=0;i<iDimX*iDimY*iDimZ;i++)
// 			{
// 				imgBufSet[i]=static_cast<unsigned char>(u[i]*255);
// 			}
// 			sprintf_s(path,"U_%d",iter);
// 			dumpBmp(path,imgBufSet,iDimX,iDimY,iDimZ,8);
// 			delete[] imgBufSet;
// 		}
		int step= int (iterationCount/5);
       if (iter==0)
	   {memset(UIterationtemp1,0,iDimX*iDimY*iDimZ*sizeof(float));
	   memcpy(UIterationtemp1,u,sizeof(float)*iDimX*iDimY*iDimZ);
       }

	   else if (iter==5)
	   {memset(UIterationtemp2,0,iDimX*iDimY*iDimZ*sizeof(float));
	   memcpy(UIterationtemp2,u,sizeof(float)*iDimX*iDimY*iDimZ);
	   }

	   else if (iter==10)
	   {memset(UIterationtemp3,0,iDimX*iDimY*iDimZ*sizeof(float));
	   memcpy(UIterationtemp3,u,sizeof(float)*iDimX*iDimY*iDimZ);
	   }

	   else if (iter==15)
	   {memset(UIterationtemp4,0,iDimX*iDimY*iDimZ*sizeof(float));
	    memcpy(UIterationtemp4,u,sizeof(float)*iDimX*iDimY*iDimZ);
	   }

	   else if (iter==20)
	   {memset(UIterationtemp5,0,iDimX*iDimY*iDimZ*sizeof(float));
	   memcpy(UIterationtemp5,u,sizeof(float)*iDimX*iDimY*iDimZ);
	   }

	}	//迭代结束
    imgBufSet=new unsigned char[iDimX*iDimY*iDimZ];
	for(int i=0;i<iDimX*iDimY*iDimZ;i++)
	{
		imgBufSet[i]=static_cast<unsigned char>(u[i]*255);
	}
	dumpBmp("Final_U",imgBufSet,iDimX,iDimY,iDimZ,8);
	delete[] imgBufSet;

	ippsFree(HistIn);
	ippsFree(HistOut);

	ippsFree(matrix);
	ippsFree(sMatrix);
	ippsFree(dx);
	ippsFree(dy);
	ippsFree(dz);
	ippsFree(gb);
	ippsFree(NormGrad);
	ippsFree(regionTermIn);
	ippsFree(regionTermOut);
	ippsFree(RegionTerm);
	ippsFree(pxu);
	ippsFree(pyu);
	ippsFree(pzu);
	ippsFree(term);
	ippsFree(termx);
	ippsFree(termy);
	ippsFree(termz);
	ippsFree(divp);
	ippsFree(result);
	ippsFree(Gb);
	ippsFree(PdfIn);
	ippsFree(PdfOut);
}
void SegFunction::post_processing(const int* iDimension,bool bSeed=false,bool cutflag=false,int istart=0,int iend=0)
{	/************************************************************************/
	/*
	后期处理
	iDimension:原始数据的维数

	bSeed:手工取种子点标记。默认为false
	iSeed:种子点坐标,默认为空

	bInterpolation：插值标记，默认为true

	cutflag：是否对原数据进行裁剪。
	istart：数据起始位置
	iend：数据终止位置

	默认情况：
	自动选取种子点
	需要完成插值处理
	*/
	/************************************************************************/


	int iDim[3];
	iDim[0]=iDimension[0];
	iDim[1]=iDimension[1];
	iDim[2]=iend-istart+1;

	//int iUNum=0;	

	

	//区域增长
   if(bSeed==false)
   {
	   printf("**fReginGrowParm%f\n",fReginGrowParm);
	   region_grow_new(fReginGrowParm);
   }

 

   if(bSeed==true)
  {
	  region_grow(pSeed,fReginGrowParm);
   }
   interpolation2ori(iDim);
   //插值处理，还原到原始数据大小。
//    unsigned char *img= new unsigned char[iDimX*iDimY];
//    for(int i=0;i<iDimY;i++)
//    {
// 	   for(int j=0;j<iDimX;j++)
// 	   {
// 		   img[(i*iDimX+j)]=static_cast<unsigned char>(u[100*iDimX*iDimY+i*iDimX+j]*255);
// 		  
// 	   }
//    }
//    saveBmp("uSeed.bmp",img,iDimX,iDimY,8);
//    delete[] img;

//	interpolation2ori(iDim);

	//生成mask文件，u>fThreU的为肝脏部分，其他为非肝脏部分。

	printf("**fThreU%f\n",fThreU);
	for(int i=0;i<iDimX*iDimY*iDimZ;i++)
	{
		if(u[i]>fThreU)
			pMask_temp[i]=LIVER_8SEGMENT_WHOLE;
		else
			pMask_temp[i]=OTHERS;
	}



	//平滑
// 	int a=int(fNorm/fSpaceZ);
// 	printf("a:%d\n",a);

	smooth(4);

// 	unsigned char* imgBufSet=new unsigned char[iDimX*iDimY*iDimZ];
// 	for(int i=0;i<iDimX*iDimY*iDimZ;i++)
// 	{
// 		imgBufSet[i]=static_cast<unsigned char>(pMask_temp[i]*100);
// 	}
// 	dumpBmp("GB_BMP",imgBufSet,iDimX,iDimY,iDimZ,8);
// 	delete[] imgBufSet;

// 	/************************************************************************/

	//补回切掉的层数
	if(cutflag==true)
	{
		cvtCut2ori(istart,iend,iDimension);
	}
// 	char *pTrans_temp=new char[iDimX*iDimY*iDimZ];
// 	for(int i=0;i<iDimZ;i++)
// 	{
// 		for(int j=0;j<iDimX*iDimY;j++)
// 		{
// 			pTrans_temp[i*this->iDimX*this->iDimY+j]=pMask_temp[(iDimZ-i-1)*this->iDimX*this->iDimY+j];
// 		}
// 	}
// 	memcpy(pMask_temp,pTrans_temp,sizeof(char)*iDimX*iDimY*iDimZ);
// 	delete[] pTrans_temp;
}
void SegFunction::region_grow(int* pSeed,char *pMask,const int *iDim)
{
	std::queue<Point3D<int>>Q;
	Point3D<int> ptSeed;
	int pageSize=iDim[0]*iDim[1];
	int maxSize=pageSize*iDim[2];
	bool *pMatrix=new bool[maxSize];
	memset(pMatrix,false,sizeof(bool)*maxSize);

	ptSeed.set(pSeed[0],pSeed[1],pSeed[2]);
	Q.push(ptSeed);

	int curPos[3];

	while(!Q.empty())
	{
		Point3D<int> &cur=Q.front();
	    pMatrix[cur.z*pageSize+cur.y*iDimX+cur.x]=true;
		char seed=pMask[cur.z*pageSize+cur.y*iDimX+cur.x];//种子点的标签
		if(cur.x-1>0&&cur.x+1<iDimX&&cur.y-1>0&&cur.y+1<iDimY&&cur.z-1>0&&cur.z+1<iDimZ)
		{
			curPos[0]=cur.x-1;
			curPos[1]=cur.y;
			curPos[2]=cur.z;
		//种子点左方
		if(pMask[curPos[2]*pageSize+curPos[1]*iDimX+curPos[0]]==seed
			&&pMatrix[curPos[2]*pageSize+curPos[1]*iDimX+curPos[0]]==false)
		{
			pMatrix[curPos[2]*pageSize+curPos[1]*iDimX+curPos[0]]=true;
			Q.push(Point3D<int>(curPos[0],curPos[1],curPos[2]));
		}

		//种子点右方
		curPos[0]=cur.x+1;
		curPos[1]=cur.y;
		curPos[2]=cur.z;
		if(pMask[curPos[2]*pageSize+curPos[1]*iDimX+curPos[0]]==seed
			&&pMatrix[curPos[2]*pageSize+curPos[1]*iDimX+curPos[0]]==false)
		{
			pMatrix[curPos[2]*pageSize+curPos[1]*iDimX+curPos[0]]=true;
			Q.push(Point3D<int>(curPos[0],curPos[1],curPos[2]));
		}

		//种子点下方
		curPos[0]=cur.x;
		curPos[1]=cur.y-1;
		curPos[2]=cur.z;
		if(pMask[curPos[2]*pageSize+curPos[1]*iDimX+curPos[0]]==seed
			&&pMatrix[curPos[2]*pageSize+curPos[1]*iDimX+curPos[0]]==false)
		{
			pMatrix[curPos[2]*pageSize+curPos[1]*iDimX+curPos[0]]=true;
			Q.push(Point3D<int>(curPos[0],curPos[1],curPos[2]));
		}
		//种子点上方
		curPos[0]=cur.x;
		curPos[1]=cur.y+1;
		curPos[2]=cur.z;
		if(pMask[curPos[2]*pageSize+curPos[1]*iDimX+curPos[0]]==seed
			&&pMatrix[curPos[2]*pageSize+curPos[1]*iDimX+curPos[0]]==false)
		{
			pMatrix[curPos[2]*pageSize+curPos[1]*iDimX+curPos[0]]=true;
			Q.push(Point3D<int>(curPos[0],curPos[1],curPos[2]));
		}
		//种子点前方
		curPos[0]=cur.x;
		curPos[1]=cur.y;
		curPos[2]=cur.z-1;
		if(pMask[curPos[2]*pageSize+curPos[1]*iDimX+curPos[0]]==seed
			&&pMatrix[curPos[2]*pageSize+curPos[1]*iDimX+curPos[0]]==false)
		{
			pMatrix[curPos[2]*pageSize+curPos[1]*iDimX+curPos[0]]=true;
			Q.push(Point3D<int>(curPos[0],curPos[1],curPos[2]));
		}
		//种子点后方
		curPos[0]=cur.x;
		curPos[1]=cur.y;
		curPos[2]=cur.z+1;
		if(pMask[curPos[2]*pageSize+curPos[1]*iDimX+curPos[0]]==seed
			&&pMatrix[curPos[2]*pageSize+curPos[1]*iDimX+curPos[0]]==false)
		{
			pMatrix[curPos[2]*pageSize+curPos[1]*iDimX+curPos[0]]=true;
			Q.push(Point3D<int>(curPos[0],curPos[1],curPos[2]));
		}
	}
	Q.pop();

	}
	for(int i=0;i<maxSize;i++)
	{
		if(pMatrix[i]==false)
		{
			pMask[i]=OTHERS;
		}
	}

}

void SegFunction::region_grow(int* pSeed,float thre)
{
	/************************************************************************/
	/* 传统的区域增长    
	*/
	/************************************************************************/
	std::queue<Point3D<int>>Q;
	Point3D<int> ptSeed;
	printf("dimx,y,z,%d,%d,%d\n",iDimX,iDimY,iDimZ);
	int pageSize=iDimX*iDimY;
	int maxSize=pageSize*iDimZ;
	bool *pMatrix=new bool[maxSize];
	memset(pMatrix,false,sizeof(bool)*maxSize);

	//设置种子点
	ptSeed.set(pSeed[0],pSeed[1],pSeed[2]);

	Q.push(ptSeed);

	int curPos[3];
	while (!Q.empty())
	{
		Point3D<int> &cur=Q.front();
		pMatrix[cur.z*pageSize+cur.y*iDimX+cur.x]=true;
		float seed=u[cur.z*pageSize+cur.y*iDimX+cur.x];
		if(cur.x-1>0&&cur.x+1<iDimX&&cur.y-1>0&&cur.y+1<iDimY&&cur.z-1>0&&cur.z+1<iDimZ)
		{
			curPos[0]=cur.x-1;
			curPos[1]=cur.y;
			curPos[2]=cur.z;
			//种子点左方
			if(abs(u[curPos[2]*pageSize+curPos[1]*iDimX+curPos[0]]-seed)<=thre
				&&pMatrix[curPos[2]*pageSize+curPos[1]*iDimX+curPos[0]]==false)
			{
				pMatrix[curPos[2]*pageSize+curPos[1]*iDimX+curPos[0]]=true;
				Q.push(Point3D<int>(curPos[0],curPos[1],curPos[2]));
			}

			//种子点右方
			curPos[0]=cur.x+1;
			curPos[1]=cur.y;
			curPos[2]=cur.z;
			if(abs(u[curPos[2]*pageSize+curPos[1]*iDimX+curPos[0]]-seed)<=thre
				&&pMatrix[curPos[2]*pageSize+curPos[1]*iDimX+curPos[0]]==false)
			{
				pMatrix[curPos[2]*pageSize+curPos[1]*iDimX+curPos[0]]=true;
				Q.push(Point3D<int>(curPos[0],curPos[1],curPos[2]));
			}

			//种子点下方
			curPos[0]=cur.x;
			curPos[1]=cur.y-1;
			curPos[2]=cur.z;
			if(abs(u[curPos[2]*pageSize+curPos[1]*iDimX+curPos[0]]-seed)<=thre
				&&pMatrix[curPos[2]*pageSize+curPos[1]*iDimX+curPos[0]]==false)
			{
				pMatrix[curPos[2]*pageSize+curPos[1]*iDimX+curPos[0]]=true;
				Q.push(Point3D<int>(curPos[0],curPos[1],curPos[2]));
			}
			//种子点上方
			curPos[0]=cur.x;
			curPos[1]=cur.y+1;
			curPos[2]=cur.z;
			if(abs(u[curPos[2]*pageSize+curPos[1]*iDimX+curPos[0]]-seed)<=thre
				&&pMatrix[curPos[2]*pageSize+curPos[1]*iDimX+curPos[0]]==false)
			{
				pMatrix[curPos[2]*pageSize+curPos[1]*iDimX+curPos[0]]=true;
				Q.push(Point3D<int>(curPos[0],curPos[1],curPos[2]));
			}
			//种子点前方
			curPos[0]=cur.x;
			curPos[1]=cur.y;
			curPos[2]=cur.z-1;
			if(abs(u[curPos[2]*pageSize+curPos[1]*iDimX+curPos[0]]-seed)<=thre
				&&pMatrix[curPos[2]*pageSize+curPos[1]*iDimX+curPos[0]]==false)
			{
				pMatrix[curPos[2]*pageSize+curPos[1]*iDimX+curPos[0]]=true;
				Q.push(Point3D<int>(curPos[0],curPos[1],curPos[2]));
			}
			//种子点后方
			curPos[0]=cur.x;
			curPos[1]=cur.y;
			curPos[2]=cur.z+1;
			if(abs(u[curPos[2]*pageSize+curPos[1]*iDimX+curPos[0]]-seed)<=thre
				&&pMatrix[curPos[2]*pageSize+curPos[1]*iDimX+curPos[0]]==false)
			{
				pMatrix[curPos[2]*pageSize+curPos[1]*iDimX+curPos[0]]=true;
				Q.push(Point3D<int>(curPos[0],curPos[1],curPos[2]));
			}
		}
		Q.pop();
	}

	//没有增长到的地方将u设为0
//#pragma parallel
	for(int i=0;i<maxSize;i++)
	{
		if(pMatrix[i]==false)
		{
			u[i]=0;
		}
		
	}
	delete[] pMatrix;
	
}

void SegFunction::interpolation2ori(int *iDimension)
{
	/************************************************************************/
	/*
	反向插值
	*/
	/************************************************************************/
	//需要插值生成的维数
		/************************************************************************/
	/*
	反向插值
	*/
	/************************************************************************/
	//需要插值生成的维数
	int iNewDimX=iDimension[0];
	int iNewDimY=iDimension[1];
	int iNewDimZ=iDimension[2];
	//插值的比例
	float ratioX=float(iDimX)/iNewDimX;
	float ratioY=float(iDimY)/iNewDimY;
	float ratioZ=float(iDimZ)/iNewDimZ;

	//x轴插值
	float *pNewU=ippsMalloc_32f(iNewDimX*iDimY*iDimZ);
     
	int pageSize=iNewDimX*iDimY;
	int oldPageSize=iDimX*iDimY;

/*#pragma parallel*/
	for(int z=0;z<iDimZ;z++)
	{
		for(int y=0;y<iDimY;y++)
		{
			for(int x=0;x<iNewDimX;x++)
			{
				int pre=static_cast<int>(floor(x*ratioX));
				int next=pre+1;

				next=(next>=iDimX?(iDimX-1):next);
				pre=(pre>=iDimX?(iDimX-1):pre);

				float tempRatio=float(1.0-abs(x*ratioX-pre));

				pNewU[z*pageSize+y*iNewDimX+x]=
					static_cast<float>(tempRatio*u[z*oldPageSize+y*iDimX+pre]+
					(1.0-tempRatio)*u[z*oldPageSize+y*iDimX+next]);
			}
		}
	}

	ippsFree(u);
	u=ippsMalloc_32f(iNewDimX*iNewDimY*iNewDimZ);
	ippsCopy_32f(pNewU,u,iNewDimX*iDimY*iDimZ);
	ippsFree(pNewU);

	//y轴
		pNewU=ippsMalloc_32f(iNewDimX*iNewDimY*iDimZ);
	pageSize=iNewDimX*iNewDimY;
	oldPageSize=iNewDimX*iDimY;

/*#pragma parallel*/
	for(int z=0;z<iDimZ;z++)
	{
		for(int y=0;y<iNewDimY;y++)
		{
			int pre=static_cast<int>(floor(y*ratioY));
			int next=pre+1;
			next=(next>=iDimY?(iDimY-1):next);
			pre=(pre>=iDimY?(iDimY-1):pre);

			float tempRatio=float(1.0-abs(y*ratioY-pre));

			for(int x=0;x<iNewDimX;x++)
			{
				pNewU[z*pageSize+y*iNewDimX+x]=
					static_cast<float>(tempRatio*u[z*oldPageSize+pre*iNewDimX+x]+
					(1.0-tempRatio)*u[z*oldPageSize+next*iNewDimX+x]);
			}
		}
	}


	ippsSet_32f(0,u,iNewDimX*iNewDimY*iNewDimZ);
	ippsCopy_32f(pNewU,u,iNewDimX*iNewDimY*iDimZ);
	ippsFree(pNewU);


	//z轴
		pNewU=ippsMalloc_32f(iNewDimX*iNewDimY*iNewDimZ);
	pageSize=iNewDimX*iNewDimY;
	oldPageSize=iNewDimX*iNewDimY;

/*#pragma parallel*/
	for(int z=0;z<iNewDimZ;z++)
	{
		int pre=static_cast<int>(floor(z*ratioZ));
		int next=pre+1;
		pre=(pre>=iDimZ?(iDimZ-1):pre);
		next=(next>=iDimZ?(iDimZ-1):next);
		float tempRatio=float(1.0-abs(z*ratioZ-pre));

		for(int y=0;y<iNewDimY;y++)
		{
			for(int x=0;x<iNewDimX;x++)
			{
				pNewU[z*pageSize+y*iNewDimX+x]=
					static_cast<float>(tempRatio*u[pre*oldPageSize+y*iNewDimX+x]+
					(1.0-tempRatio)*u[next*oldPageSize+y*iNewDimX+x]);
			}
		}
	}

	ippsSet_32f(0,u,iNewDimX*iNewDimY*iNewDimZ);
	ippsCopy_32f(pNewU,u,iNewDimX*iNewDimY*iNewDimZ);
	ippsFree(pNewU);

	//设置当前的维度
	iDimX=iNewDimX;
	iDimY=iNewDimY;
	iDimZ=iNewDimZ;
}

void SegFunction::find_seed_U()
{
	//找到u的最大值
	//u最大值的坐标x，y,z为种子点。
	float max=-1;
//	int imax=0;

	int m=0;
	for(int i=0;i<iDimZ;i++)
	for(int j=0;j<iDimY;j++)
	for(int k=0;k<iDimX;k++)
	{
		if(k<iDimY-1-j&&u[m]>max){
			max=u[m];
		    pSeed[0]=k;
		    pSeed[1]=j;
		    pSeed[2]=i;
		}
		m++;
	}
}

void SegFunction::pre_threshold(int iGain,int iCT)
{
	//预处理阈值
	//iCut：整体减掉的值
	//iMax: 减掉后的最大值
	printf("pre_threshold1:%d iGain=%d iCT=%d\n", pData_temp[6*iDimX*iDimY+45*iDimX+45],iGain,iCT);
	printf("iMaxIm:%d\n",iMaxIm);
	for(int i=0;i<iDimX*iDimY*iDimZ;i++)
	{
		pData_temp[i]=short(pData_temp[i]-(iGain+iCT-iMaxIm/2));
		if(pData_temp[i]<0)pData_temp[i]=0;
		if(pData_temp[i]>=iMaxIm)pData_temp[i]=short(iMaxIm-1);
	}
/*	printf("pre_threshold: iGain=%d, iCT=%d, iMaxIm=%d\n",iGain,iCT,iMaxIm);*/
//	printf("pre_threshold2:%d\n", pData_temp[6*iDimX*iDimY+45*iDimX+45]);
	                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
}
void SegFunction::interpolation(float fNorm)
{
	//插值函数。
	//以z轴为放缩标准。fNorm为z轴需要放缩的比例

	//计算放缩比例
	float ratioX=fNorm/fSpaceX;
	float ratioY=fNorm/fSpaceY;
	float ratioZ=fNorm/fSpaceZ;
	printf("ratio: %f %f %f\n",ratioX,ratioY,ratioZ);

	//放缩以后生成的新维度
	int iNewDimX=static_cast<int>(floor((iDimX-1.0)/ratioX)+1);
	int iNewDimY=static_cast<int>(floor((iDimY-1.0)/ratioY)+1);
	int iNewDimZ=static_cast<int>(floor((iDimZ-1.0)/ratioZ)+1);

	//x轴插值
	int temp=this->tempNum; //缓存区长度
	float *pData_tempf=new float[temp];

	for(int i=0;i<temp;i++) pData_tempf[i]= static_cast<float>(pData_temp[i]);

	float *pNewData=new float[iNewDimX*iDimY*iDimZ];

	int pageSize=iNewDimX*iDimY;
	int oldPageSize=iDimX*iDimY;

//#pragma parallel
	for(int z=0;z<iDimZ;z++)
	{
		for(int y=0;y<iDimY;y++)
		{
			for(int x=0;x<iNewDimX;x++)
			{
				int pre=static_cast<int>(floor(x*ratioX));
				int next=pre+1;

				next=(next>=iDimX?(iDimX-1):next);
				float tempRatio=float(1.0-abs(x*ratioX-pre));

				pNewData[z*pageSize+y*iNewDimX+x]=float(tempRatio*pData_tempf[z*oldPageSize+y*iDimX+pre]+
					(1.0-tempRatio)*pData_tempf[z*oldPageSize+y*iDimX+next]);
			}
		}
	}
	
	memcpy(pData_tempf,pNewData,iNewDimX*iDimY*iDimZ*sizeof(float));
	
	delete[] pNewData;

	//y轴插值
	pNewData=new float[iNewDimX*iNewDimY*iDimZ];
	pageSize=iNewDimX*iNewDimY;
	oldPageSize=iNewDimX*iDimY;

//#pragma parallel
	for(int z=0;z<iDimZ;z++)
	{
		for(int y=0;y<iNewDimY;y++)
		{
			int pre=static_cast<int>(floor(y*ratioY));
			int next=pre+1;
			next=(next>=iDimY?(iDimY-1):next);
			float tempRatio=1-abs(y*ratioY-pre);

			for(int x=0;x<iNewDimX;x++)
			{
				pNewData[z*pageSize+y*iNewDimX+x]=tempRatio*pData_tempf[z*oldPageSize+pre*iNewDimX+x]+
					(1-tempRatio)*pData_tempf[z*oldPageSize+next*iNewDimX+x];
			}
		}
	}
	memcpy(pData_tempf,pNewData,iNewDimX*iNewDimY*iDimZ*sizeof(float));
	delete[] pNewData;

	//z轴插值
	pNewData=new float[iNewDimX*iNewDimY*iNewDimZ];
	pageSize=iNewDimX*iNewDimY;
	oldPageSize=iNewDimX*iNewDimY;

//#pragma parallel
	for(int z=0;z<iNewDimZ;z++)
	{
		int pre=static_cast<int>(floor(z*ratioZ));
		int next=pre+1;
		next=(next>=iDimZ?(iDimZ-1):next);
		float tempRatio=1-abs(z*ratioZ-pre);

		for(int y=0;y<iNewDimY;y++)
		{
			for(int x=0;x<iNewDimX;x++)
			{

				pNewData[z*pageSize+y*iNewDimX+x]=tempRatio*pData_tempf[pre*oldPageSize+y*iNewDimX+x]+
					(1-tempRatio)*pData_tempf[next*oldPageSize+y*iNewDimX+x];
			}
		}
	}
	memcpy(pData_tempf,pNewData,iNewDimX*iNewDimY*iNewDimZ*sizeof(float));
	for(int i=0;i<iNewDimX*iNewDimY*iNewDimZ;i++) pData_temp[i]= static_cast<short>(pData_tempf[i]);

	delete[] pNewData;
	delete[] pData_tempf;

	//设置当前维度
	iDimX=iNewDimX;
	iDimY=iNewDimY;
	iDimZ=iNewDimZ;

}

void SegFunction::cut_page(int iStart,int iEnd)
{
	//截取istart到iEnd之间的值
	//istart：肝脏起始页面
	//iEnd:肝脏终止页面

	short *imgSet=new short[iDimX*iDimY*(iEnd-iStart+1)];
	int n=0;
	for(int i=iStart;i<=iEnd;i++)
	{
		for(int j=0;j<iDimY;j++)
		{
			for(int k=0;k<iDimX;k++)
			
			imgSet[n++]=pData_temp[i*iDimX*iDimY+j*iDimX+k];
		}
	}
	memset(pData_temp,0,tempNum*sizeof(short));
	memcpy(pData_temp,imgSet,iDimX*iDimY*(iEnd-iStart+1)*sizeof(short));
	delete[] imgSet;
	
	//更新当前z轴维度。
	iDimZ=iEnd-iStart+1;

}

void SegFunction::cvtCut2ori(int iStart,int iEnd,const int* iDim)
{
	//补回截掉页面
	//iStart:肝脏初始页面
	//iEnd：肝脏结束页面
	//iDim:原始体数据维度

	char * imgMask=new char[iDim[0]*iDim[1]*iDim[2]];
 	memset(imgMask,OTHERS,iDim[0]*iDim[1]*iDim[2]*sizeof(char));

// 	unsigned char* imgBufSet=new unsigned char[iDimX*iDimY*iDimZ];
// 	for(int i=0;i<iDimX*iDimY*iDimZ;i++)
// 	{
// 		imgBufSet[i]=static_cast<unsigned char>(pMask_temp[i]*100);
// 	}
// 	dumpBmp("GB_BMP",imgBufSet,iDimX,iDimY,iDimZ,8);
// 	delete[] imgBufSet;

 	int m=0;
 	for(int i=iStart;i<=iEnd;i++)
 	{
 		for(int j=0;j<iDim[1];j++)
 		{
 			for(int k=0;k<iDim[0];k++)
 			{
 				imgMask[i*iDim[0]*iDim[1]+j*iDim[0]+k]=pMask_temp[m++];
 			}
 		}
 	}
 	delete[] pMask_temp;
	pMask_temp=new char[iDim[0]*iDim[1]*iDim[2]];
 	memcpy(pMask_temp,imgMask,iDim[0]*iDim[1]*iDim[2]*sizeof(char));
 	delete[] imgMask;
	iDimZ=iDim[2];

// 	imgBufSet=new unsigned char[iDimX*iDimY*iDimZ];
// 	for(int i=0;i<iDimX*iDimY*iDimZ;i++)
// 	{
// 		imgBufSet[i]=static_cast<unsigned char>(pMask_temp[i]*100);
// 	}
// 	dumpBmp("GB_BMP",imgBufSet,iDimX,iDimY,iDimZ,8);
// 	delete[] imgBufSet;

}

/*
 *
 *   Function: 优化后的三维高斯函数
 *
 *   smatrix：高斯函数生成的结果
 *   nKsize：模板大小 7
 *	 gama: 伽马值 1
 *	 matrix：需要处理的矩阵
 *   iDimX iDimY iDimZ： 原始图像的XYZ，均为全局变量
 * 
 */
void SegFunction::Gaussian_3D(float *smatrix,int nKsize,float gama,float* matrix)
{
	
	

	float* pKernel= ippsMalloc_32f(nKsize);
	float kSum=0;
	int i,j,k,m;

	//生成高斯模板
	i=-nKsize/2;
	for(;i<=nKsize/2;i++)
	{
		pKernel[i+nKsize/2]=exp(-i*i/(2*gama*gama));
		kSum+=pKernel[i+nKsize/2];
	}

	for(i=0;i<nKsize;i++)
	{
			pKernel[i]/=kSum;//归一化
			//printf("%.8f ",pKernel[i]);
	}

	//做高斯，边界采用对称方案

	float* tempArry=ippsMalloc_32f(iDimX*iDimY*iDimZ);


	//x方向
	//printf("gassian\n");
	//printf("X...\n");
	for(k=0;k<iDimZ;k++)
	{
		for(j=0;j<iDimY;j++)
		{
			for(int i=0;i<iDimX;i++)
			{
				kSum=0;
				for(m=-nKsize/2;m<=nKsize/2;m++)
				{
					int mm=(i+m);
					if(mm<0) mm=-mm;
					if(mm>=iDimX) mm=2*(iDimX-1)-mm;

					kSum+=matrix[k*iDimX*iDimY+j*iDimX+mm]*pKernel[m+nKsize/2];

				}
				tempArry[k*iDimX*iDimY+j*iDimX+i]=kSum;

			}
		}
	}
	ippsSet_32f(0,smatrix,iDimX*iDimY*iDimZ);
    ippsCopy_32f(tempArry,smatrix,iDimX*iDimY*iDimZ);
	//y方向
	//printf("Y...\n");
	for(k=0;k<iDimZ;k++)
	{
		for(i=0;i<iDimX;i++)
		{
			for(int j=0;j<iDimY;j++)
			{
				kSum=0;
				for(m=-nKsize/2;m<=nKsize/2;m++)
				{
					int mm=(j+m);
					if(mm<0) mm=-mm;
					if(mm>=iDimY) mm=2*(iDimY-1)-mm;

					kSum+=smatrix[k*iDimX*iDimY+mm*iDimX+i]*pKernel[m+nKsize/2];

				}
				tempArry[k*iDimX*iDimY+j*iDimX+i]=kSum;

			}
		}
	}

	ippsSet_32f(0,smatrix,iDimX*iDimY*iDimZ);
	ippsCopy_32f(tempArry,smatrix,iDimX*iDimY*iDimZ);


	//z方向
	//printf("Z...\n");
	for(j=0;j<iDimY;j++)
	{
		for(i=0;i<iDimX;i++)
		{
			for(int k=0;k<iDimZ;k++)
			{
				kSum=0;
				for(m=-nKsize/2;m<=nKsize/2;m++)
				//for(m=nKsize/2;m>=-nKsize/2;m--)
				{
					int mm=(k+m);
					if(mm<0) mm=-mm;
					if(mm>=iDimZ) mm=2*(iDimZ-1)-mm;

					kSum+=smatrix[mm*iDimX*iDimY+j*iDimX+i]*pKernel[m+nKsize/2];

				}
				tempArry[k*iDimX*iDimY+j*iDimX+i]=kSum;

			}
		}
	}

	ippsSet_32f(0,smatrix,iDimX*iDimY*iDimZ);
	ippsCopy_32f(tempArry,smatrix,iDimX*iDimY*iDimZ);

	ippsFree(tempArry);
	ippsFree(pKernel);

}

/*
 *
 *   Function: 优化后的三维高斯函数   !!! 给定iDimension
 *
 *   smatrix：高斯函数生成的结果
 *   nKsize：模板大小 7
 *	 gama: 伽马值 1
 *	 matrix：需要处理的矩阵
 *   iDim： 给定图像的XYZ
 * 
 */
void SegFunction::Gaussian_3D(float *smatrix,int nKsize,float gama,float* matrix,const int *iDim)
{
	int iDimX, iDimY, iDimZ;
	iDimX = iDim[0];
	iDimY = iDim[1];
	iDimZ = iDim[2];

	float* pKernel= ippsMalloc_32f(nKsize);
	float kSum=0;
	int i,j,k,m;

	//生成高斯模板
	i=-nKsize/2;
	for(;i<=nKsize/2;i++)
	{
		pKernel[i+nKsize/2]=exp(-i*i/(2*gama*gama));
		kSum+=pKernel[i+nKsize/2];
	}

	for(i=0;i<nKsize;i++)
	{
			pKernel[i]/=kSum;//归一化
			//printf("%.8f ",pKernel[i]);
	}

	//做高斯，边界采用对称方案

	float* tempArry=ippsMalloc_32f(iDimX*iDimY*iDimZ);


	//x方向
	//printf("gassian\n");
	//printf("X...\n");
	for(k=0;k<iDimZ;k++)
	{
		for(j=0;j<iDimY;j++)
		{
			for(int i=0;i<iDimX;i++)
			{
				kSum=0;
				for(m=-nKsize/2;m<=nKsize/2;m++)
				{
					int mm=(i+m);
					if(mm<0) mm=-mm;
					if(mm>=iDimX) mm=2*(iDimX-1)-mm;

					kSum+=matrix[k*iDimX*iDimY+j*iDimX+mm]*pKernel[m+nKsize/2];

				}
				tempArry[k*iDimX*iDimY+j*iDimX+i]=kSum;

			}
		}
	}
	ippsSet_32f(0,smatrix,iDimX*iDimY*iDimZ);
    ippsCopy_32f(tempArry,smatrix,iDimX*iDimY*iDimZ);
	//y方向
	//printf("Y...\n");
	for(k=0;k<iDimZ;k++)
	{
		for(i=0;i<iDimX;i++)
		{
			for(int j=0;j<iDimY;j++)
			{
				kSum=0;
				for(m=-nKsize/2;m<=nKsize/2;m++)
				{
					int mm=(j+m);
					if(mm<0) mm=-mm;
					if(mm>=iDimY) mm=2*(iDimY-1)-mm;

					kSum+=smatrix[k*iDimX*iDimY+mm*iDimX+i]*pKernel[m+nKsize/2];

				}
				tempArry[k*iDimX*iDimY+j*iDimX+i]=kSum;

			}
		}
	}

	ippsSet_32f(0,smatrix,iDimX*iDimY*iDimZ);
	ippsCopy_32f(tempArry,smatrix,iDimX*iDimY*iDimZ);


	//z方向
	//printf("Z...\n");
	for(j=0;j<iDimY;j++)
	{
		for(i=0;i<iDimX;i++)
		{
			for(int k=0;k<iDimZ;k++)
			{
				kSum=0;
				for(m=-nKsize/2;m<=nKsize/2;m++)
				//for(m=nKsize/2;m>=-nKsize/2;m--)
				{
					int mm=(k+m);
					if(mm<0) mm=-mm;
					if(mm>=iDimZ) mm=2*(iDimZ-1)-mm;

					kSum+=smatrix[mm*iDimX*iDimY+j*iDimX+i]*pKernel[m+nKsize/2];

				}
				tempArry[k*iDimX*iDimY+j*iDimX+i]=kSum;

			}
		}
	}

	ippsSet_32f(0,smatrix,iDimX*iDimY*iDimZ);
	ippsCopy_32f(tempArry,smatrix,iDimX*iDimY*iDimZ);

	ippsFree(tempArry);
	ippsFree(pKernel);

}

void SegFunction::Gaussian_2D(float *smatrix,int wid,int heigh,int nKsize,float gama,float* matrix)
{
	//优化的二维的高斯平滑
	//smatrix：高斯优化的结果
	//wid：图片的宽度
	//heigh:图片的高度
	//nKsize:高斯模板大小
	//gama:高斯平滑伽马值
	//matrix:需要平滑的图片。

	float* pKernel=new float[nKsize];
	float kSum=0;
	int i,j,m;

	//生成二维高斯模板
	i=-nKsize/2;
	for(;i<=nKsize/2;i++)
	{
		pKernel[i+nKsize/2]=float(exp(-i*i/(2*gama*gama)));
		kSum+=pKernel[i+nKsize/2];
		//printf("%.8f\n",kSum);
	}
// 	for(i=0;i<nKsize;i++)
// 	{
// 		printf("%.8f\n",pKernel[i]);
// 	}
	for(i=0;i<nKsize;i++)
		pKernel[i]/=kSum;//归一化	
// 	printf("\n after\n");
// 	for(i=0;i<nKsize;i++)
// 	{
// 		printf("%.8f\n",pKernel[i]);
// 	}
	//做高斯，边界采用对称方案

	float* tempArry=new float [wid*heigh];


	//x方向
	//printf("gassian\n");
	//printf("X...\n");
	for(j=0;j<heigh;j++)
		{
			for(int i=0;i<wid;i++)
			{
				kSum=0;
				for(m=-nKsize/2;m<=nKsize/2;m++)
				{
					int mm=(i+m);
					if(mm<0) mm=-mm;
					if(mm>=wid) mm=2*(wid-1)-mm;

					kSum+=matrix[j*wid+mm]*pKernel[m+nKsize/2];

				}
				tempArry[j*wid+i]=kSum;

			}
		}
	
	memset(smatrix,0,wid*heigh*sizeof(float));
	memcpy(smatrix,tempArry,wid*heigh*sizeof(float));

	//y方向
	//printf("Y...\n");
		for(i=0;i<wid;i++)
		{
			for(int j=0;j<heigh;j++)
			{
				kSum=0;
			//	for(m=-nKsize/2;m<=nKsize/2;m++)
				for(m=nKsize/2;m>=-nKsize/2;m--)
				{
					int mm=(j+m);
					if(mm<0) mm=-mm;
					if(mm>=heigh) mm=2*(heigh-1)-mm;

					kSum+=smatrix[mm*wid+i]*pKernel[m+nKsize/2];

				}
				tempArry[j*wid+i]=kSum;

			}
		}

		memset(smatrix,0,wid*heigh*sizeof(float));
		memcpy(smatrix,tempArry,wid*heigh*sizeof(float));

	delete[] tempArry;
	delete[] pKernel;

}
void SegFunction::ComputeGb( float *data, int width, int height, int depth, float *Gb, float *NormGrad )
{
	//边缘检测函数。
	//data:需要处理的数据
	//width:图片的宽度
	//height:图片的高度
	//depth :图片的深度。

	//different g(x) definition change here
	Gradient( data, width, height, depth, NormGrad);

	int totalLength = width*height*depth;
	//		memset(Gb,0,sizeof(float)*totalLength);
	//		memset(NormGrad,0,sizeof(float)*totalLength);
	for (int i = 0; i < totalLength; i++)
		Gb[i] = float(1.0 / (1.0 + beta * NormGrad[i] * NormGrad[i]));
}

void SegFunction::InitUV( float* data, float* _u, float* _v)
{
	//初始化u，v；
	//平扫期采用u = 1.0-abs(Im0/maxIm-0.5).*2;
	//增强期采用u = 2.0*u;
	//u(u>1)=1.0-2.5*(u(u>1)-1.0);
	int m=0;
//	#pragma parallel
	for (int k = 0; k < iDimZ; k++){
	    for (int j = 0; j < iDimY; j++){
	        for (int i = 0; i < iDimX; i++){
				if(iContrastFlag==NON_CONTRAST){
					_u[m]=float(1.0-abs(data[m]/iMaxIm-0.5)*2);
				}else if(iContrastFlag==ENHANCE_CONTRAST){
					_u[m]=float(data[m]*2.0/iMaxIm);
					if(_u[m]>1)	_u[m]=float(1.0-2.5*(_u[m]-1.0));//这个地方试是2.5，不是2
					if(_u[m]<0)	_u[m]=0;
				}
				if(i>iDimY-1-j+60/fNorm)_u[m]=0;
            	_v[m]=_u[m];
				m++;
			}
		}
	}
}

void SegFunction::Backwardx( float* data, float* dx, int width, int height, int depth )
{
//对x轴的后向偏导
    int index=0;
	for(int z=0;z<depth;z++)
	{
		for(int y=0;y<height;y++)
		{
//			#pragma ivdep
			for(int x=0;x<width;x++)
			{
				if(x==0||y==0||z==0||y==height-1||z==depth-1)
					dx[index]=data[index];
				else if(x==width-1)
					dx[index]=-data[index-1];
				else
					dx[index]=data[index]-data[index-1];
				index++;
			}
		}
	}
}

void SegFunction::Backwardy( float* data, float* dy, int width, int height, int depth )
{
//对y轴的后向偏导

	int index=0;
	for(int z=0;z<depth;z++)
	{
		for(int y=0;y<height;y++)
		{
//			#pragma ivdep
			for(int x=0;x<width;x++)
			{
				if(x==0||y==0||z==0||x==width-1||z==depth-1)
					dy[index]=data[index];
				else if(y==height-1)
					dy[index]=-data[index-width];
				else
					dy[index]=data[index]-data[index-width];
				index++;
			}
		}
	}

}

void SegFunction::Backwardz( float* data, float* dz, int width, int height, int depth )
{
//对z轴的后向偏导
	int index=0; int wh=width*height;
	for(int z=0;z<depth;z++)
	{
		for(int y=0;y<height;y++)
		{
//			#pragma ivdep
			for(int x=0;x<width;x++)
			{
				if(x==0||y==0||z==0||x==width-1||y==height-1)
					dz[index]=data[index];
				else if(z==depth-1)
					dz[index]=-data[index-wh];
				else
					dz[index]=data[index]-data[index-wh];
				index++;
			}
		}
	}
}

void SegFunction::Forwardx( float* data, float* dx, int width, int height, int depth )
{
//对x轴的前向偏导
	int index=0;
	for(int z=0;z<depth;z++)
	{
		for(int y=0;y<height;y++)
		{
			for(int x=0;x<width;x++)
			{
				if(x==width-1||y==height-1||z==depth-1)
					dx[index]=0;
				else
					dx[index]=data[index+1]-data[index];
				index++;
			}
		}
	}
}

void SegFunction::Forwardy( float* data, float* dy, int width, int height, int depth )
{
//对y轴的前向偏导
	int index=0;
	for(int z=0;z<depth;z++)
	{
		for(int y=0;y<height;y++)
		{
			for(int x=0;x<width;x++)
			{
				if(x==width-1||y==height-1||z==depth-1)
					dy[index]=0;
				else
					dy[index]=data[index+width]-data[index];
				index++;
			}
		}
	}
}

void SegFunction::Forwardz( float* data, float* dz, int width, int height, int depth )
{
//对z轴的前向偏导
	int index=0; int wh=width*height;
	for(int z=0;z<depth;z++)
	{
		for(int y=0;y<height;y++)
		{
			for(int x=0;x<width;x++)
			{
				if(x==width-1||y==height-1||z==depth-1)
					dz[index]=0;
				else
					dz[index]=data[index+wh]-data[index];
				index++;
			}
		}
	}

}

void SegFunction::Gradient( float *data, int width, int height, int depth, float *NormGrad )
{
	//求数据的梯度
	//先求x,y,z轴三个方向的偏导
	Forwardx( data, dx, width, height, depth );
	Forwardy( data, dy, width, height, depth );
	Forwardz( data, dz, width, height, depth );
	
	int totalLength = width*height*depth;
	//求梯度
	for (int i = 0; i < totalLength; i++)
		NormGrad[i] = sqrt( dx[i] * dx[i] + dy[i] * dy[i] + dz[i] * dz[i] );
}

void SegFunction::conv_aid(float *x, float* h, int lenX, int lenH, float *result){
	//这里强制假定lenX >= lenH
	//序列x和h的线性卷积，lenX和lenH分别是两序列长度，
	//返回result，其长度为lenX + lenH - 1
		memset(result, 0, (lenX + lenH - 1) * sizeof(float));
//	#pragma parallel
//	#pragma loop count min(512,lenH)
	for (int i = 0; i < lenH; i++){
		for (int j = 0; j <= i; j++)
			result[i] += x[j] * h[i - j];
	}
//    #pragma parallel
//	#pragma loop count min(512,leX)
	for (int i = lenH; i < lenX; i++){
		for (int j = 0; j <lenH; j++)
			result[i] += x[i - j] * h[j];
	}
//	#pragma parallel
//	#pragma loop count min(128, lenX + lenH - 1)
	for (int i = lenX; i < lenX + lenH - 1; i++){
		for (int j = i - lenX + 1; j < lenH; j++)
			result[i] += x[i - j] * h[j];
	}
}
void SegFunction::conv(float *x, float *h, int lenX, int lenH, float *result){
	//一维卷积
	if (lenX >= lenH)
		conv_aid(x, h, lenX, lenH, result);
	else
		conv_aid(h, x, lenH, lenX, result);
}
//  void SegFunction::localMaximun(float * H,int iDimZ, int iCuredeRange ,int *xIn,int *yIn,int& pointNum)
//  {
//  	//找局部最大值
//  	/************************************************************************/
//  	/*
//  	H:为需要找的局部最大值的二维数组。
//  	dim:为维数
//  	xIn：x的坐标数组
//  	yIn：y的坐标数组
//  	
//  	返回所有局部最大是的x,y的数组。
//  	*/
//  	/************************************************************************/
//  
//  	/************************************************************************/
//  	/*
//  	   算法描述：
//  	   按照minDist矩阵进行膨胀操作。
//  	   膨胀后图像跟原图像相等的点为局部最大值。
//  	   膨胀规则：
//  	       在iminDist矩阵中扩展比种子点小的点。
//  	*/
//  	/************************************************************************/
//  	//模板大小：
//  	int modelX=(iMinDis-1)/2;
//  	int modelY=(iMinDis-1)/2;
//  
//  	//膨胀
//  	float *dialateH=new float[iDimZ*iCuredeRange];
//  	memset(dialateH,0,sizeof(float)*iDimZ*iCuredeRange);
//  
//  	for(int i=0;i<iDimZ;i++)
//  	{
//  		for(int j=0;j<iCuredeRange;j++)
//  		{
//  			float kernel=H[i*iCuredeRange+j];
//  			for(int ii=i-modelY;ii<=i+modelY;ii++)
//  			{
//  				for(int jj=j-modelX;jj<=jj+modelX;jj++)
//  				{
//  					if(ii>=0&&ii<iDimZ&&jj>=0&&jj<=iCurdeLow)
//  					{
//  						if(dialateH[ii*iCuredeRange+jj]<kernel)
//  						{
//  							dialateH[ii*iCuredeRange+jj]=kernel;
//  						}
//  					}
//  				}
//  			}
//  		}
//  	}
//  
//  	//找最大点
//  
//  	for(int i=0;i<iDimZ;i++)
//  	{
//  		for(int j=0;j<iCuredeRange;j++)
//  		{
//  			if(dialateH[i*iCuredeRange+j]==H[i*iCuredeRange+j])
//  			{
//  				xIn[pointNum]=j;
//  				yIn[pointNum]=i;
//  				pointNum++;
//  			}
//  		}
//  	}
//  }
 void SegFunction::localMaximun(float * H,int wid, int heigh ,int *xIn,int *yIn,int& pointNum)
 {
 	//找局部最大值
 	/************************************************************************/
 	/*
 	H:为需要找的局部最大值的二维数组。
 	dim:为维数
 	xIn：x的坐标数组
 	yIn：y的坐标数组
 	
 	返回所有局部最大是的x,y的数组。
 	*/
 	/************************************************************************/
 
 	/************************************************************************/
 	/*
 	   算法描述：
 	   按照minDist矩阵进行膨胀操作。
 	   膨胀后图像跟原图像相等的点为局部最大值。
 	   膨胀规则：
 	       在iminDist矩阵中扩展比种子点小的点。
 	*/
 	/************************************************************************/
 	//模板大小：
 
 	pointNum=0;
 
 	for(int i=1;i<heigh-1;i++)
 	{
 		for(int j=1;j<wid-1;j++)
 		{
 			//找这样一个点：该点大于周围的八邻域，并且大于八领域的平均值。
 			//这样的点设定为局部最大值点。
 			float kennl=H[i*wid+j];
 			float sum=0;
 
 			if(kennl<H[i*wid+j-1])continue;
 			if(kennl<H[i*wid+j+1])continue;
 			if(kennl<H[(i-1)*wid+j])continue;
 			if(kennl<H[(i+1)*wid+j])continue;
 
 			if(kennl<H[(i-1)*wid+j-1])continue;
 			if(kennl<H[(i-1)*wid+j+1])continue;
 			if(kennl<H[(i+1)*wid+j-1])continue;
 			if(kennl<H[(i+1)*wid+j+1])continue;
 			
 			sum=H[i*wid+j-1]+H[i*wid+j+1]+H[(i-1)*wid+j]+H[(i+1)*wid+j]+
 				H[(i-1)*wid+j-1]+H[(i-1)*wid+j+1]+H[(i+1)*wid+j-1]+H[(i+1)*wid+j+1];
 
 			if(kennl*8<=sum)continue;
 			if(pointNum>0)
 			{
 				if(j-xIn[pointNum-1]<iMinDis&&i-yIn[pointNum-1]<iMinDis)continue;
 	
 			}
 			xIn[pointNum]=j;
 			yIn[pointNum]=i;
 			pointNum++;
 /*         	printf("point %d xIn: %d yIn: %d \n",pointNum,j,i);*/
 
 		}
 	}
 	printf("pointNum=%d, wid=%d, heigh=%d\n",pointNum, wid, heigh);
 }

/*****************************************
* 函数名称：
*     saveBmp()
*
*函数参数：
*    char *bmpName-文件名字及路径
*    unsigned char *imgBuf-待存盘的位图数据
*    int width-以像素为单位待存盘位图的宽
*    int  height-以像素为单位待存盘位图高
*    int biBitCount-每像素所占位数
*    RGBQUAD *pColorTable-颜色表指针
*返回值：
*    0为失败，1为成功
*
*说明：给定一个图像位图数据、宽、高、颜色表指针及每像素所占的位数等信息，
*      将其写到指定文件中
******************************************
*****************************/


bool SegFunction::saveBmp(char *bmpName, unsigned char *imgBuf, int width, int height, int biBitCount)
{
	int pColorTable[256];
	pColorTable[0]=0;
	for(int i=1;i<256;i++)pColorTable[i]=pColorTable[i-1] + 0x10101;
	//如果位图数据指针为0，则没有数据传入，函数返回
	if(!imgBuf)
		return 0;
	//颜色表大小，以字节为单位，灰度图像颜色表为1024字节，彩色图像颜色表大小为0
	int colorTablesize=0;
	if(biBitCount==8)colorTablesize=1024;
	//待存储图像数据每行字节数为4的倍数
	int lineByte=(width * biBitCount/8+3)/4*4;

	//以二进制写的方式打开文件
	FILE *fp;
	if(fopen_s(&fp,bmpName,"wb")!=0)return 0;
	
	//申请位图文件头结构变量，填写文件头信息
	BITMAPFILEHEADER fileHead;
	fileHead.bfType = 0x4D42;//bmp类型
	//bfSize是图像文件4个组成部分之和
	fileHead.bfSize= sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + colorTablesize + lineByte*height;
	fileHead.bfReserved1 = 0;
	fileHead.bfReserved2 = 0;
	//bfOffBits是图像文件前3个部分所需空间之和
	fileHead.bfOffBits=54+colorTablesize;
	//写文件头进文件
	fwrite(&fileHead, sizeof(BITMAPFILEHEADER),1, fp);
	//申请位图信息头结构变量，填写信息头信息
	BITMAPINFOHEADER head; 
	head.biBitCount=(WORD)biBitCount;
	head.biClrImportant=0;
	head.biClrUsed=0;
	head.biCompression=0;
	head.biHeight=height;
	head.biPlanes=1;
	head.biSize=40;
	head.biSizeImage=lineByte*height;
	head.biWidth=width;
	head.biXPelsPerMeter=0;
	head.biYPelsPerMeter=0;
	//写位图信息头进内存
	fwrite(&head, sizeof(BITMAPINFOHEADER),1, fp);
	//如果灰度图像，有颜色表，写入文件 
	if(biBitCount==8)fwrite(pColorTable, sizeof(RGBQUAD),256, fp);
	//写位图数据进文件
	for(int i=0;i<height;i++){
		if(biBitCount==8)fwrite(&imgBuf[(height-1-i)*width], lineByte, 1, fp);
		else fwrite(&imgBuf[(height-1-i)*width*3], lineByte, 1, fp);
	}

	//关闭文件
	fclose(fp);
	//	printf("lineByte=%d\n",lineByte);
	return 1;

}

//bool SegFunction::saveBmp(char *bmpName, float *imgBuf, int width, int height, int biBitCount)
//{
//  int pColorTable[256];
//	pColorTable[0]=0;
//	for(int i=1;i<256;i++)pColorTable[i]=pColorTable[i-1] + 0x10101;
//	//如果位图数据指针为0，则没有数据传入，函数返回
//	if(!imgBuf)
//		return 0;
//	//颜色表大小，以字节为单位，灰度图像颜色表为1024字节，彩色图像颜色表大小为0
//	int colorTablesize=0;
//	if(biBitCount==8)colorTablesize=1024;
//	//待存储图像数据每行字节数为4的倍数
//	int lineByte=(width * biBitCount/8+3)/4*4;
//
//	//以二进制写的方式打开文件
//	FILE *fp;
//	if(fopen_s(&fp,bmpName,"wb")!=0)return 0;
//	
//	//申请位图文件头结构变量，填写文件头信息
//	BITMAPFILEHEADER fileHead;
//	fileHead.bfType = 0x4D42;//bmp类型
//	//bfSize是图像文件4个组成部分之和
//	fileHead.bfSize= sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + colorTablesize + lineByte*height;
//	fileHead.bfReserved1 = 0;
//	fileHead.bfReserved2 = 0;
//	//bfOffBits是图像文件前3个部分所需空间之和
//	fileHead.bfOffBits=54+colorTablesize;
//	//写文件头进文件
//	fwrite(&fileHead, sizeof(BITMAPFILEHEADER),1, fp);
//	//申请位图信息头结构变量，填写信息头信息
//	BITMAPINFOHEADER head; 
//	head.biBitCount=(WORD)biBitCount;
//	head.biClrImportant=0;
//	head.biClrUsed=0;
//	head.biCompression=0;
//	head.biHeight=height;
//	head.biPlanes=1;
//	head.biSize=40;
//	head.biSizeImage=lineByte*height;
//	head.biWidth=width;
//	head.biXPelsPerMeter=0;
//	head.biYPelsPerMeter=0;
//	//写位图信息头进内存
//	fwrite(&head, sizeof(BITMAPINFOHEADER),1, fp);
//	//如果灰度图像，有颜色表，写入文件 
//	if(biBitCount==8)fwrite(pColorTable, sizeof(RGBQUAD),256, fp);
//	//写位图数据进文件
//	for(int i=0;i<height;i++){
//		if(biBitCount==8)fwrite(&imgBuf[(height-1-i)*width], lineByte, 1, fp);
//		else fwrite(&imgBuf[(height-1-i)*width*3], lineByte, 1, fp);
//	}
//
//	//关闭文件
//	fclose(fp);
//	//	printf("lineByte=%d\n",lineByte);
//	return 1;
//
//}

bool SegFunction::dumpBmp(char *dirName, unsigned char *imgBufSet, int width, int height, int num ,int biBitCount)
{
	char fileName[50];
	unsigned char * imgBuf;
	if(biBitCount==24)imgBuf=new unsigned char[width*height*3];
	else imgBuf=new unsigned char[width*height];

	if(_mkdir(dirName)==0){
		printf("%s created \n",dirName);
	}else{
		printf("%s has exist \n",dirName);
	}
	if(biBitCount==24){
		for(int i=0;i<num;i++){
			for(int j=0;j<width*height*3;j++){
				imgBuf[j]=imgBufSet[i*width*height*3+j];
			}
			sprintf_s(fileName,"%s//%d.bmp",dirName,i);
			saveBmp(fileName,imgBuf,width,height,biBitCount);
		}
	}else{
		for(int i=0;i<num;i++){
			for(int j=0;j<width*height;j++){
				imgBuf[j]=imgBufSet[i*width*height+j];
			}
			sprintf_s(fileName,"%s//%d.bmp",dirName,i);
			saveBmp(fileName,imgBuf,width,height,biBitCount);
		}
	}

	return(0);
}

 void SegFunction::region_grow_new(float thre)
 {


	 /************************************************************************/
	 /* 修改后的区域增长                                                                     */
	 /************************************************************************/
	  /************************************************************************/
	 /*
	 //算法思想：
	 //1、统计u大于阈值thre的所有点的个数，计为iUNumAll
	 //2、在未进行区域增长的图片对角线左上方寻找u[i]值最大的点为种子点，并记下x,y,z为种子点坐标。
	 //3、根据第二步找到的种子点进行传统的区域增长，并记下该次区域增长的点的个数为，iUNumNow。
	 //   计算未标记的点的个数为iUNumRemain。
	 //4、更新最大区域的点的个数maxNum，对应最大区域点的标号maxflag；
	 //5、当未标记点的个数小于已标记点的最大个数时停止循环。否则重复2-5步。
	 //6、拥有maxflag标号的增长区域即为所得的最后区域增长结果。
	 */
	 /************************************************************************/
std::queue<Point3D<int>>Q;
	 Point3D<int> ptSeed;
	 int pageSize=iDimX*iDimY;
	 int maxSize=pageSize*iDimZ;
	 int *pMatrix=new int[maxSize];
	 int iUNumAll=0;
	 int iUNumNow=0;
	 int iUNumRemain=0;
	 int flagNum=1;
	 int maxflag;
	 int maxNum;
	 maxNum=0;
	 maxflag=0;
	 memset(pMatrix,0,sizeof(int)*maxSize);
	 printf("thre: %f\n",thre);
	 printf("fThreU: %f\n",fThreU);
	 int m=0;
	  //1、统计u大于阈值thre的所有点的个数，计为iUNumAll
	 for(int i=0;i<iDimZ;i++)
	 {
		 for(int j=0;j<iDimY;j++)
		 {
			 for(int k=0;k<iDimX;k++)
			 {

				 if(u[m]<=fThreU||i==0||j==0||k==0||i==iDimZ-1||j==iDimY-1||k==iDimX-1)
				 {	
					 u[m]=0.0;
				 }else if(k<iDimY-1-j)iUNumAll++;
				 m++;
			 }
		 }
	 }

	 iUNumRemain=iUNumAll;

	 printf("volume:%d  iUNumAll：%d \n",iDimX*iDimY*iDimZ,iUNumAll);
	 while(iUNumRemain>maxNum){
		 //2、在未进行区域增长的图片对角线左上方寻找u[i]值最大的点为种子点，并记下x,y,z为种子点坐标。
	  	 float max=-1;	  
	  	 m=0;
		 for(int i=0;i<iDimZ;i++)
		 {
			for(int j=0;j<iDimY;j++)
	  		{	 for(int k=0;k<iDimX;k++)
	  			 {
	  				 if(k<iDimY-1-j&&u[m]>max&&pMatrix[m]==0)
					 {//对角线左上部分找。
	  					 max=u[m];
	  					 pSeed[0]=k;
	  					 pSeed[1]=j;
	  					 pSeed[2]=i;
	  				 }
					 m++;
				 }
			 }
	
		 }
		 if(max<0)break;
		ptSeed.set(pSeed[0],pSeed[1],pSeed[2]);
		flagNum++;
		//printf("x:%d y:%d z:%d\n",pSeed[0],pSeed[1],pSeed[2]);
		//printf("flagNum %d",flagNum);
		Q.push(ptSeed);
		iUNumNow=1;

		int curPos[3];
		int m;
		while (!Q.empty())
		{
			//3、根据第二步找到的种子点进行传统的区域增长，并记下该次区域增长的点的个数为，iUNumNow。
			//区域增长不选择斜点增长。即只增长上、下、左、右、前、后
			Point3D<int> &cur=Q.front();
	        m=cur.z*pageSize+cur.y*iDimX+cur.x;
			pMatrix[m]=flagNum;
			float seed=u[m];
			if(cur.x-1>0&&cur.x+1<iDimX&&cur.y-1>0&&cur.y+1<iDimY&&cur.z>0&&cur.z+1<iDimZ)
			{
				curPos[0]=cur.x-1;
				curPos[1]=cur.y;
				curPos[2]=cur.z;
			    m=curPos[2]*pageSize+curPos[1]*iDimX+curPos[0];
				if(abs(u[m]-seed)<=thre && u[m]>fThreU && pMatrix[m]==0){
					pMatrix[m]=flagNum;
					Q.push(Point3D<int>(curPos[0],curPos[1],curPos[2]));
					if(curPos[0]<iDimY-1-curPos[1])iUNumNow++;
				}

				curPos[0]=cur.x+1;
				curPos[1]=cur.y;
				curPos[2]=cur.z;
			    m=curPos[2]*pageSize+curPos[1]*iDimX+curPos[0];
				if(abs(u[m]-seed)<=thre	&& u[m]>fThreU &&pMatrix[m]==0){
					pMatrix[m]=flagNum;
					Q.push(Point3D<int>(curPos[0],curPos[1],curPos[2]));
					if(curPos[0]<iDimY-1-curPos[1])iUNumNow++;
				}

				curPos[0]=cur.x;
				curPos[1]=cur.y-1;
				curPos[2]=cur.z;
			    m=curPos[2]*pageSize+curPos[1]*iDimX+curPos[0];
				if(abs(u[m]-seed)<=thre	&& u[m]>fThreU &&pMatrix[m]==0){
					pMatrix[m]=flagNum;
					Q.push(Point3D<int>(curPos[0],curPos[1],curPos[2]));
					if(curPos[0]<iDimY-1-curPos[1])iUNumNow++;
				}

				curPos[0]=cur.x;
				curPos[1]=cur.y+1;
				curPos[2]=cur.z;
			    m=curPos[2]*pageSize+curPos[1]*iDimX+curPos[0];
				if(abs(u[m]-seed)<=thre	&& u[m]>fThreU &&pMatrix[m]==0){
					pMatrix[m]=flagNum;
					Q.push(Point3D<int>(curPos[0],curPos[1],curPos[2]));
					if(curPos[0]<iDimY-1-curPos[1])iUNumNow++;
				}

				curPos[0]=cur.x;
				curPos[1]=cur.y;
				curPos[2]=cur.z-1;
			    m=curPos[2]*pageSize+curPos[1]*iDimX+curPos[0];
				if(abs(u[m]-seed)<=thre	&& u[m]>fThreU &&pMatrix[m]==0){
					pMatrix[m]=flagNum;
					Q.push(Point3D<int>(curPos[0],curPos[1],curPos[2]));
					if(curPos[0]<iDimY-1-curPos[1])iUNumNow++;
				}

				curPos[0]=cur.x;
				curPos[1]=cur.y;
				curPos[2]=cur.z+1;
			    m=curPos[2]*pageSize+curPos[1]*iDimX+curPos[0];
				if(abs(u[m]-seed)<=thre	&& u[m]>fThreU &&pMatrix[m]==0){
					pMatrix[m]=flagNum;
					Q.push(Point3D<int>(curPos[0],curPos[1],curPos[2]));
					if(curPos[0]<iDimY-1-curPos[1])iUNumNow++;
				}
			}
		    Q.pop();
		}
		//计算未标记的点的个数为iUNumRemain。
		iUNumRemain=iUNumRemain-iUNumNow;
		
		if(iUNumNow>maxNum){
			 //4、更新最大区域的点的个数maxNum，对应最大区域点的标号maxflag；
			maxNum=iUNumNow;
			maxflag=flagNum;
		printf("maxNum: %d  maxflag: %d \n",maxNum,maxflag);
		}
		
	} //5、当未标记点的个数小于已标记点的最大个数时停止循环。否则重复2-5步。
		 flagNum=maxflag;
	 printf("flagNum: %d\n",flagNum);
	  //6、拥有maxflag标号的增长区域即为所得的最后区域增长结果。
//#pragma parallel
	 for(int i=0;i<maxSize;i++)
	 {
		 if(pMatrix[i]!=flagNum)
		 {
			 u[i]=0;
		 }
	 }
	 delete[] pMatrix;
 }
int SegFunction::generate_plane_3point(const int *a,const int *b,const int *c,int *plane)
{
	//判断三点是否在一条直线上
	//plane 平面的四个参数（Ax+By+Cz+D=0）


	if((a[0]*b[1]*c[2]+a[1]*b[2]*c[0]+a[2]*b[0]*c[1]-a[2]*b[1]*c[0]-a[1]*b[0]*c[2]-a[0]*b[2]*c[1])==0)
	{
		printf("3 point in the same line\n");
		return 0;
	}

	int m1[3];
	int m2[3];
	
	for(int i=0;i<3;i++)
	{
		m1[i]=b[i]-a[i];
		m2[i]=c[i]-a[i];
	}


	plane[0]=m1[1]*m2[2]-m1[2]*m2[1];//A
	plane[1]=m1[2]*m2[0]-m1[0]*m2[2];//B
	plane[2]=m1[0]*m2[1]-m1[1]*m2[0];//C



	plane[3]=-(plane[0]*a[0]+plane[1]*a[1]+plane[2]*a[2]);//D=-(Ax+By+Cz)

//	printf("plane %d %d %d %d \n",plane[0],plane[1],plane[2],plane[3]);
	return 1;

}

//中心线文件已知的情况下进行八段分割,文档中的第二种方法
bool SegFunction::seg_mask_8(const char *pAllMask,const char *centerLineName,char *pMask,const int *iDim)
{
	int vein[3]={0};
	int veinM[3]={0};
	int veinR[3]={0};
	int portal[3]={0};
	int portalL[3]={0};
	int portalLineR=0;
	int portalLineL=0;

	int point[45];
	if(seg_mask_8_centerline(centerLineName,vein,veinR,veinM,portal,portalL,&portalLineL,&portalLineR,point))
	//CbibSeg::seg_mask_8(pAllMask,point,pMask,support.iDimension);
	return seg_mask_8(pAllMask,vein,veinR,veinM,portal,portalL,portalLineL,portalLineR,pMask,iDim);
	else
		return false;
}

bool SegFunction::find_place(int *m1,int*m2,int *aim,float& cosValue)
{
	//叉积判断方向，cos返回角度大小
	float v1=float(m1[0]*m2[0]+m1[1]*m2[1]+m1[2]*m2[2]);
	float va=float(m1[0]*m1[0]+m1[1]*m1[1]+m1[2]*m1[2]);
	float vb=float(m2[0]*m2[0]+m2[1]*m2[1]+m2[2]*m2[2]);


	cosValue=v1/sqrt(va*vb);
	int c[3];
	c[0]=m1[1]*m2[2]-m1[2]*m2[1];//A
	c[1]=m1[2]*m2[0]-m1[0]*m2[2];//B
	c[2]=m1[0]*m2[1]-m1[1]*m2[0];//C

	if(c[0]*aim[0]+c[1]*aim[1]+c[2]*aim[2]<0)return true;
	else return false;
}

bool SegFunction::seg_mask_8(const char *pAllMask,int* point,char *pMask,const int *iDim)
{
	
	if(point==NULL)return false;
	
	int plane[4];
	//第一刀
	generate_plane_3point(&point[0],&point[3],&point[6],plane);
	printf("1: plane %dx+ %dy+ %dz+ %d =0\n",plane[0],plane[1],plane[2],plane[3]);
	int m=0;
	for(int i=0;i<iDim[2];i++)
	{
		for(int j=0;j<iDim[1];j++)
		{
			for(int k=0;k<iDim[0];k++)
			{
				 m=(iDim[2]-1-i)*iDim[0]*iDim[1]+j*iDim[0]+k;
				if(pAllMask[m]==LIVER_8SEGMENT_WHOLE)
				{
					int ans=k*plane[0]+j*plane[1]+i*plane[2]+plane[3];//ans=Ax+By+Cz+D;
					if(ans<0)
						pMask[m]=LIVER_8SEGMENT_PART2;
					else
						pMask[m]=LIVER_8SEGMENT_PART1;
				}
				else
				{
					pMask[m]=0;
				}
// 
// 				m++;
			}
		}
	}

	//第二刀
	generate_plane_3point(&point[9],&point[12],&point[15],plane);
// 	for(int i=9;i<16;i++)
// 	{
// 		printf("%d,",point[i]);
// 		if(i%3==2)printf("  ");
// 	}
	printf("\n2: plane %dx+ %dy+ %dz+ %d =0\n",plane[0],plane[1],plane[2],plane[3]);
	m=0;
	for(int i=0;i<iDim[2];i++)
	{
		for(int j=0;j<iDim[1];j++)
		{
			for(int k=0;k<iDim[0];k++)
			{
				 m=(iDim[2]-1-i)*iDim[0]*iDim[1]+j*iDim[0]+k;
				if(pMask[m]==LIVER_8SEGMENT_PART1)
				{
					int ans=k*plane[0]+j*plane[1]+i*plane[2]+plane[3];//ans=Ax+By+Cz+D;
					if(ans<0)
						pMask[m]=LIVER_8SEGMENT_PART8;
					else
						pMask[m]=LIVER_8SEGMENT_PART7;
				}
			/*	m++;*/
			}
		}
	}
// 	//第三刀
// 	generate_plane_3point(&point[18],&point[21],&point[24],plane);
// 	printf("plane %dx+ %dy+ %dz+ %d =0\n",plane[0],plane[1],plane[2],plane[3]);
    plane[0]=0;
	plane[1]=0;
	plane[2]=1;
	plane[3]=point[26];
	m=0;
	printf("\n3: plane %dx+ %dy+ %dz+ %d =0\n",plane[0],plane[1],plane[2],plane[3]);
	for(int i=0;i<iDim[2];i++)
	{
		for(int j=0;j<iDim[1];j++)
		{
			for(int k=0;k<iDim[0];k++)
			{
				 m=(iDim[2]-1-i)*iDim[0]*iDim[1]+j*iDim[0]+k;
				if(pMask[m]==LIVER_8SEGMENT_PART7||pMask[m]==LIVER_8SEGMENT_PART8)
				{
					int ans=k*plane[0]+j*plane[1]+i*plane[2]+plane[3];//ans=Ax+By+Cz+D;
			     	if(ans<0)
				    {
					   if(pMask[m]==LIVER_8SEGMENT_PART7)pMask[m]=LIVER_8SEGMENT_PART7;
					   if(pMask[m]==LIVER_8SEGMENT_PART8)pMask[m]=LIVER_8SEGMENT_PART8;
				    }
					else
					{
						if(pMask[m]==LIVER_8SEGMENT_PART7)pMask[m]=LIVER_8SEGMENT_PART6;
						if(pMask[m]==LIVER_8SEGMENT_PART8)pMask[m]=LIVER_8SEGMENT_PART5;
					}
				}
// 
// 				m++;
			}
		}
	}
// 
// 	//第四刀
	generate_plane_3point(&point[27],&point[30],&point[33],plane);
	printf("4: plane %dx+ %dy+ %dz+ %d =0\n",plane[0],plane[1],plane[2],plane[3]);
	if(plane[0]>0)
	{
		plane[0]=-plane[0];
		plane[1]=-plane[1];
		plane[2]=-plane[2];
		plane[3]=-plane[3];
	}
	m=0;
	for(int i=0;i<iDim[2];i++)
	{
		for(int j=0;j<iDim[1];j++)
		{
			for(int k=0;k<iDim[0];k++)
			{
				 m=(iDim[2]-1-i)*iDim[0]*iDim[1]+j*iDim[0]+k;
				if(pMask[m]==LIVER_8SEGMENT_PART2)
				{
					int ans=k*plane[0]+j*plane[1]+i*plane[2]+plane[3];//ans=Ax+By+Cz+D;
					if(ans<0)
					{
						pMask[m]=LIVER_8SEGMENT_PART2;

					}
					else
					{
						pMask[m]=LIVER_8SEGMENT_PART4;
					}
				}

			/*	m++;*/
			}
		}
	}

// 
// 	//第五刀
// 	generate_plane_3point(&point[36],&point[39],&point[42],plane);
// 	printf("plane %dx+ %dy+ %dz+ %d =0\n",plane[0],plane[1],plane[2],plane[3]);
	plane[0]=0;
	plane[1]=0;
	plane[2]=1;
	plane[3]=point[44];
	printf("\n5: plane %dx+ %dy+ %dz+ %d =0\n",plane[0],plane[1],plane[2],plane[3]);
	m=0;
	for(int i=0;i<iDim[2];i++)
	{
		for(int j=0;j<iDim[1];j++)
		{
			for(int k=0;k<iDim[0];k++)
			{ 
				m=(iDim[2]-1-i)*iDim[0]*iDim[1]+j*iDim[0]+k;
				if(pMask[m]==LIVER_8SEGMENT_PART2)
				{
					int ans=k*plane[0]+j*plane[1]+i*plane[2]+plane[3];//ans=Ax+By+Cz+D;
					if(ans<0)
					{
						pMask[m]=LIVER_8SEGMENT_PART2;

					}
					else
					{
						pMask[m]=LIVER_8SEGMENT_PART3;
					}
				}

			/*	m++;*/
			}
		}
	}
	return true;
}
void SegFunction::seg_tumour(const int *seed,short *pData_base,const char *pAllMask,int* iDimension,const float * fSpace,char *pMask)
{
	//pData_base:
	//pAllMask:肝脏分割的结果
	//iDimension：维数
	//fSpace：分辨率
	//pMask:肝脏分割结果

	//另一套参数分割出肝脏结果，pMask


	int seedtumour[3];
	seedtumour[0]=(seed[0]+seed[3])/2;
	seedtumour[1]=(seed[1]+seed[4])/2;
	seedtumour[2]=(seed[2]+seed[5])/2;

	int volumeSize=iDimension[0]*iDimension[1]*iDimension[2];
	unsigned char* imgBufSet = new unsigned char [volumeSize*3];
	short * pData_show=new short[volumeSize];
	memcpy(pData_show,pData_base,volumeSize*sizeof(short));

	
	if(pAllMask[seedtumour[2]*iDimension[0]*iDimension[1]+seedtumour[1]*iDimension[0]+seedtumour[0]]==OTHERS){
		printf("seed is out:\n");

		//种子点在肝脏外面
	initParm("parm_out.config");
	//showParm();
	liversegment(pData_base,iDimension,fSpace,false,NULL,pMask,&bHaveVessel);

	for(int i=0;i<volumeSize;i++)
	{
		int im=int(pData_show[i]-1024);
		if(im<0)
		{
			im=0;
			imgBufSet[3*i]=(char)im;
			imgBufSet[3*i+1]=(char)im;
			imgBufSet[3*i+2]=(char)im;
		}
		else if(im>255)
		{
			im=255;
			imgBufSet[3*i]=(char)im;
			imgBufSet[3*i+1]=(char)im;
			imgBufSet[3*i+2]=(char)im;
		}
		else
		{
			imgBufSet[3*i]=(char)im;
			imgBufSet[3*i+1]=(char)im;
			imgBufSet[3*i+2]=(char)im;
			if(pAllMask[i]==LIVER_8SEGMENT_WHOLE)
			{
					imgBufSet[3*i+1]=(char)(((30+im)<255)?(30+im):255);
			}
			if(pMask[i]==LIVER_8SEGMENT_WHOLE)
			{
				imgBufSet[3*i+2]=(char)(((30+im)<255)?(30+im):255);
			}
		}

	}
	dumpBmp("LiverSeg2",imgBufSet,iDimension[0],iDimension[1],iDimension[2],24);
	delete[] imgBufSet;


	//提取两个mask的插值
	for(int i=0;i<volumeSize;i++)
	{
		if((pMask[i]==LIVER_8SEGMENT_WHOLE&&pAllMask[i]==OTHERS)||(pMask[i]==OTHERS&&pAllMask[i]==LIVER_8SEGMENT_WHOLE))
		{
			pMask[i]=LEISION1;
		}
		else
		{
			pMask[i]=OTHERS;
		}
	}

	imgBufSet = new unsigned char [volumeSize*3];
	for(int i=0;i<volumeSize;i++)
	{
		int im=int(pData_show[i]-1024);
		if(im<0)
		{
			im=0;
			imgBufSet[3*i]=(char)im;
			imgBufSet[3*i+1]=(char)im;
			imgBufSet[3*i+2]=(char)im;
		}
		else if(im>255)
		{
			im=255;
			imgBufSet[3*i]=(char)im;
			imgBufSet[3*i+1]=(char)im;
			imgBufSet[3*i+2]=(char)im;
		}
		else
		{
			imgBufSet[3*i]=(char)im;
			imgBufSet[3*i+1]=(char)im;
			imgBufSet[3*i+2]=(char)im;
			if(pMask[i]==LEISION1)
				imgBufSet[3*i+1]=(char)(((30+im)<255)?(30+im):255);
			if(i==seedtumour[2]*iDimension[0]*iDimension[1]+seedtumour[1]*iDimension[0]+seedtumour[0])
			{
				imgBufSet[i*3]=0;
				imgBufSet[i*3+1]=0;
				imgBufSet[i*3+2]=255;
			}
		}

	}
	dumpBmp("cut",imgBufSet,iDimension[0],iDimension[1],iDimension[2],24);
	delete[] imgBufSet;
	//区域增长
	region_grow(seedtumour,pMask,iDimension);

	//显示
	imgBufSet = new unsigned char [volumeSize*3];
	for(int i=0;i<volumeSize;i++)
	{
		int im=int(pData_show[i]-1024);
		if(im<0)
		{
			im=0;
			imgBufSet[3*i]=(char)im;
			imgBufSet[3*i+1]=(char)im;
			imgBufSet[3*i+2]=(char)im;
		}
		else if(im>255)
		{
			im=255;
			imgBufSet[3*i]=(char)im;
			imgBufSet[3*i+1]=(char)im;
			imgBufSet[3*i+2]=(char)im;
		}
		else
		{
			imgBufSet[3*i]=(char)im;
			imgBufSet[3*i+1]=(char)im;
			imgBufSet[3*i+2]=(char)im;
			if(pAllMask[i]==LIVER_8SEGMENT_WHOLE)
				imgBufSet[3*i+2]=(char)(((30+im)<255)?(30+im):255);
			if(pMask[i]==LEISION1)
				imgBufSet[3*i+1]=(char)(((30+im)<255)?(30+im):255);
			if(i==seedtumour[2]*iDimension[0]*iDimension[1]+seedtumour[1]*iDimension[0]+seedtumour[0])
			{
				imgBufSet[i*3]=0;
				imgBufSet[i*3+1]=0;
				imgBufSet[i*3+2]=255;
			}
		}

	}
	dumpBmp("regionGorw",imgBufSet,iDimension[0],iDimension[1],iDimension[2],24);
	delete[] imgBufSet;
	delete[] pData_show;

	//生成pMask
	for(int i=0;i<volumeSize;i++)
	{
		if(pMask[i]!=LEISION1)
		{
			if(pAllMask[i]==LIVER_8SEGMENT_WHOLE)
				pMask[i]=LIVER_8SEGMENT_WHOLE;
			else
				pMask[i]=OTHERS;
		}
	}
	}
	else{
		//种子点在肝脏内部
		printf("seed is in\n");
		seg_tumour_in(seed,pData_base,pAllMask,iDimension,fSpace,pMask);
	}
}


void SegFunction::seg_tumour_in(const int *seed,short *pData_base,const char *pAllMask,int* iDimension,const float * fSpace,char *pMask)
{
	//分割肝脏肿瘤
	//pData_base：原始数据
	//pAllMask:全肝掩膜
	//iDimension：维数
	//fSpace:分辨率
	//肿瘤Mask.

	//对图片进行平滑处理,解决曝光不足问题。  
	
	//test1:高斯滤波
	initParm("parm_in.config");
	fNorm=fSpace[2];
	showParm();

	iDimX=iDimension[0];
	iDimY=iDimension[1];
	iDimZ=iDimension[2];
	fSpaceX=fSpace[0];
	fSpaceY=fSpace[1];
	fSpaceZ=fSpace[2];


	int volumSize=iDimension[0]*iDimension[1]*iDimension[2];
	float *matrix;
	float *sMatrix;
	sMatrix=ippsMalloc_32f(volumSize);
	matrix=ippsMalloc_32f(volumSize);

	//初始化参数
	std_Gb=fStdGbParm/fNorm;
	beta=float(fBataParm/(iMaxIm*iMaxIm)/fNorm);
	theta=float(1.0/fThetaParm);
	lambda=1.0f/theta*fLambdaParm;
	dt=float(1.0/fDtParm);
	std_pwm=fStdPwmParm;
	NbIterUpdate=iNbIterUpdateParm;
	int Ng=static_cast<int>(ceil(fNgParm*std_Gb))+1;

	for (int i=0;i<volumSize;i++)
	{
		matrix[i]=(float)pData_base[i];

	}

	//高斯平滑

	printf("Gaussian_3D Ng=%d std_Gb=%f\n",Ng,std_Gb);
	Gaussian_3D(sMatrix,Ng,std_Gb,matrix);

	int seedtumour[3];
	seedtumour[0]=(seed[0]+seed[3])/2;
	seedtumour[1]=(seed[1]+seed[4])/2;
	seedtumour[2]=(seed[2]+seed[5])/2;
	
	float ratio=fSpaceX/fSpaceZ;

	float radius=float((seedtumour[0]-seed[0])*(seedtumour[0]-seed[0])+(seedtumour[1]-seed[1])*(seedtumour[1]-seed[1]))+float((seedtumour[2]-seed[2])*(seedtumour[2]-seed[2]))*ratio*ratio;
	radius=sqrt(radius);

	int seedLiver[3]; 
	seedLiver[0]=seedtumour[0]+int(radius*1.2f);
	seedLiver[1]=seedtumour[1]+int(radius*1.2f);
	seedLiver[2]=seedtumour[2];

	unsigned char* imgBufSet = new unsigned char [volumSize*3];
	for(int i=0;i<volumSize;i++)
	{
		int im=int(sMatrix[i]-1024);
		if(im<0)
		{
			im=0;
			imgBufSet[3*i]=(char)im;
			imgBufSet[3*i+1]=(char)im;
			imgBufSet[3*i+2]=(char)im;
		}
		else if(im>255)
		{
			im=255;
			imgBufSet[3*i]=(char)im;
			imgBufSet[3*i+1]=(char)im;
			imgBufSet[3*i+2]=(char)im;
		}
		else
		{
			imgBufSet[3*i]=(char)im;
			imgBufSet[3*i+1]=(char)im;
			imgBufSet[3*i+2]=(char)im;

			if(i==seedtumour[2]*iDimX*iDimY+seedtumour[1]*iDimX+seedtumour[0])
			{
				imgBufSet[i*3]=0;
				imgBufSet[i*3+1]=0;
				imgBufSet[i*3+2]=255;
			}
			if(i==seedLiver[2]*iDimX*iDimY+seedLiver[1]*iDimX+seedLiver[0])
			{
				imgBufSet[i*3]=0;
				imgBufSet[i*3+2]=0;
				imgBufSet[i*3+1]=255;
			}
		}
	
	}

	dumpBmp("Guassian_1",imgBufSet,iDimension[0],iDimension[1],iDimension[2],24);
	printf("radius: %.4f\n",radius);
	printf("seedTumour: %d,%d,%d \n",seedtumour[0],seedtumour[1],seedtumour[2]);
	printf("seedLiver: %d,%d,%d \n",seedLiver[0],seedLiver[1],seedLiver[2]);



	delete[] imgBufSet;
    ippsFree(matrix);
	//根据种子点统计肿瘤特征值、肝脏特征值
	int iFeatureTumour=0;//肿瘤特征值
	int iFeatureLiver=0;//肝脏特征值
	int count=0;
	//肿瘤特征值
	for(int z=seedtumour[2]-5;z<=seedtumour[2]+5;z++)
	{
		for(int y=seedtumour[1]-5;y<=seedtumour[1]+5;y++)
		{
			for(int x=seedtumour[0]-5;x<=seedtumour[0]+5;x++)
			{
				int index=z*iDimX*iDimY+y*iDimX+x;
				if(pAllMask[index]==LIVER_8SEGMENT_WHOLE)
				{
					count++;
					iFeatureTumour+=(int)sMatrix[index];
				}
			}
		}
	}
	iFeatureTumour/=count;
	printf("count:%d,iFeatureTumour %d, react: %d\n",count,iFeatureTumour,iFeatureTumour-1024);

    //肝脏特征值
	count=0;
	for(int z=seedLiver[2]-5;z<=seedLiver[2]+5;z++)
	{
		for(int y=seedLiver[1]-5;y<=seedLiver[1]+5;y++)
		{
			for(int x=seedLiver[0]-5;x<=seedLiver[0]+5;x++)
			{
				int index=z*iDimX*iDimY+y*iDimX+x;
				if(pAllMask[index]==LIVER_8SEGMENT_WHOLE)
				{
					count++;
					iFeatureLiver+=(int)sMatrix[index];
				}
			}
		}
	}
	iFeatureLiver/=count;
	printf("count:%d,iFeatureLiver %d, react: %d\n",count,iFeatureLiver,iFeatureLiver-1024);
	
	//找外切立方体并赋值
	//先假设肿瘤是暗点

	int ct_mid=0;
	int ct_low=0;
	int ct_high=0;
    ct_mid=abs(iFeatureTumour-iFeatureLiver)/2;
	if (ct_mid<30)ct_mid=30;
	ct_low=(iFeatureTumour<iFeatureLiver)?(iFeatureTumour-ct_mid):(iFeatureLiver-ct_mid);
	ct_high=(iFeatureTumour<iFeatureTumour)?(iFeatureLiver+ct_mid):(iFeatureTumour+ct_mid);
	
	printf("ct_mid:%d ct_low:%d ( %d),ct_high: %d ( %d)\n",ct_mid,ct_low,ct_low-1024,ct_high,ct_high-1024);
	int iDimX_low=1000,iDimY_low=1000,iDimZ_low=1000;
	int iDimX_high=0,iDimY_high=0,iDimZ_high=0;

	printf("Ng: %d",Ng);

	int r=int(radius)+Ng*2;

	iDimX_low=seedtumour[0]-r;
	iDimX_high=seedtumour[0]+r;

	iDimY_low=seedtumour[1]-r;
	iDimY_high=seedtumour[1]+r;

	iDimZ_low=int(seedtumour[2]-r*ratio);
	iDimZ_high=int(seedtumour[2]+r*ratio);

    imgBufSet = new unsigned char [volumSize*3]; 
	for(int i=0;i<iDimension[2];i++)
	{
		for(int j=0;j<iDimension[1];j++)
		{
			for(int k=0;k<iDimension[0];k++)
			{
				int index=i*iDimension[0]*iDimension[1]+j*iDimension[0]+k;
				int im=int(sMatrix[index]-1024);
				if(im<0)
				{
					im=0;
					imgBufSet[3*index]=(char)im;
					imgBufSet[3*index+1]=(char)im;
					imgBufSet[3*index+2]=(char)im;
				}
				else if(im>255)
				{
					im=255;
					imgBufSet[3*index]=(char)im;
					imgBufSet[3*index+1]=(char)im;
					imgBufSet[3*index+2]=(char)im;
				}else
				{
					imgBufSet[3*index]=(char)im;
					imgBufSet[3*index+1]=(char)im;
					imgBufSet[3*index+2]=(char)im;

					if(i>iDimZ_low&&i<iDimZ_high&&j>iDimY_low&&j<iDimY_high&&k>iDimX_low&&k<iDimX_high)
					{
						if(im+30<255)
						imgBufSet[3*index+2]=(char)(im+30);
						
					}

				}

			}
		}
	}

	dumpBmp("RIO",imgBufSet,iDimension[0],iDimension[1],iDimension[2],24);

	iDimX=iDimX_high-iDimX_low+1;
	iDimY=iDimY_high-iDimY_low+1;
	iDimZ=iDimZ_high-iDimZ_low+1;
	fSpaceX=fSpace[0];
	fSpaceY=fSpace[1];
	fSpaceZ=fSpace[2];
	tempNum=iDimX*iDimY*iDimZ;
	int iDim[3];
	iDim[0]=iDimX;
	iDim[1]=iDimY; 
	iDim[2]=iDimZ;

	pData_temp=new short[iDimX*iDimY*iDimZ];
	pMask_temp=new char[iDimX*iDimY*iDimZ];

	//生成pData_temp;
	iMaxIm=ct_high-ct_low;
	int m=0;
	int index;

	for(int i=iDimZ_low;i<=iDimZ_high;i++)
	{
	 	for(int j=iDimY_low;j<=iDimY_high;j++)
	 	{
	 		for(int k=iDimX_low;k<=iDimX_high;k++)
	 		{
	 			index=i*iDimension[0]*iDimension[1]+j*iDimension[0]+k;
                		
	 			if(pAllMask[index]==LIVER_8SEGMENT_WHOLE)
	 			{
					int v=(int)sMatrix[index];
					if(v<ct_low)v=0;
					else if(v>ct_high)v=iMaxIm;
					else
						v=v-ct_low+1;
					pData_temp[m]=(short)v;
	 			
	 		    }
 	 			else
 	 			{
 	 				pData_temp[m]=0;
 	 			}
				
	 			m++;
	 		}
	 	}
	}
	ippsFree(sMatrix);
// 

 	printf("RAW：ct_high:%d, ct_low:%d, iMaxIm:%d \n",ct_high,ct_low,iMaxIm);


	imgBufSet=new unsigned char[iDimX*iDimY*iDimZ];

	for(int i=0;i<iDimX*iDimY*iDimZ;i++)
	{		
		int a=pData_temp[i]+ct_low-1024;
		if(a>255)a=255;
		if(a<0)a=0;
		imgBufSet[i]=(unsigned char )a;
	}
	dumpBmp("pData_temp",imgBufSet,iDimX,iDimY,iDimZ,8);
	delete[] imgBufSet;

	interpolation(fNorm);

// 	int Ng;
// 	int volumnSize;
// 	float *matrix;
	//初始化参数
	std_Gb=fStdGbParm/fNorm;
	beta=float(fBataParm/(iMaxIm*iMaxIm)/fNorm);
	theta=float(1.0/fThetaParm);
	lambda=1.0f/theta*fLambdaParm;
	dt=float(1.0/fDtParm);
	std_pwm=fStdPwmParm;
	NbIterUpdate=iNbIterUpdateParm;
	Ng=static_cast<int>(ceil(fNgParm*std_Gb))+1;
	printf("Ng: %d",Ng);
	int volumnSize=iDimX*iDimY*iDimZ;

	sMatrix=ippsMalloc_32f(volumnSize);
	dx=ippsMalloc_32f(volumnSize);
	dy=ippsMalloc_32f(volumnSize);
	dz=ippsMalloc_32f(volumnSize);
	gb=ippsMalloc_32f(volumnSize);
	NormGrad=ippsMalloc_32f(volumnSize);
	u=ippsMalloc_32f(volumnSize);
	v=ippsMalloc_32f(volumnSize);
	regionTermIn=ippsMalloc_32f(volumnSize);
	regionTermOut=ippsMalloc_32f(volumnSize);
	RegionTerm=ippsMalloc_32f(volumnSize);
	pxu=ippsMalloc_32f(volumnSize);
	pyu=ippsMalloc_32f(volumnSize);
	pzu=ippsMalloc_32f(volumnSize);
	term=ippsMalloc_32f(volumnSize);
	termx=ippsMalloc_32f(volumnSize);
	termy=ippsMalloc_32f(volumnSize);
	termz=ippsMalloc_32f(volumnSize);
	divp=ippsMalloc_32f(volumnSize);
	HistIn=ippsMalloc_32s(iMaxIm);
	HistOut=ippsMalloc_32s(iMaxIm);
	result=ippsMalloc_32f(512);
	PdfIn=ippsMalloc_32f(iMaxIm);
	PdfOut=ippsMalloc_32f(iMaxIm);
	Gb=ippsMalloc_32f(volumnSize);
	matrix=ippsMalloc_32f(volumnSize);


	//将原始数据转换成float型，并赋值给matrix。
	for (int i=0;i<volumnSize;i++)
	{
		matrix[i]=(float)pData_temp[i];
	}


	//高斯滤波 
	//对图像进行高斯滤波，平滑。
	printf("Gaussian_3D Ng=%d std_Gb=%f\n",Ng,std_Gb);
	Gaussian_3D(sMatrix,Ng,std_Gb,matrix);
	imgBufSet=new unsigned char[iDimX*iDimY*iDimZ];
	for(int i=0;i<iDimX*iDimY*iDimZ;i++)
	{		
		imgBufSet[i]=unsigned char (sMatrix[i]+ct_low-1024);
	}
	dumpBmp("Gaussian_3D",imgBufSet,iDimX,iDimY,iDimZ,8);
	delete[] imgBufSet;
	//计算边缘侦查函数
	ComputeGb(sMatrix,iDimX,iDimY,iDimZ,Gb,NormGrad);


	imgBufSet=new unsigned char[iDimX*iDimY*iDimZ];
	for(int i=0;i<iDimX*iDimY*iDimZ;i++)
	{		
		imgBufSet[i]=unsigned char(Gb[i]*255);
	}
	dumpBmp("Gb",imgBufSet,iDimX,iDimY,iDimZ,8);
	delete[] imgBufSet;

	//初始化VU
	//让u、v在0-1之间
	//	InitUV(matrix,u,v,volumnSize);
	for(int m=0;m<iDimX*iDimY*iDimZ;m++)
	{
		u[m]=matrix[m]/iMaxIm;
		if(u[m]>1)u[m]=1.0f;
		if(u[m]<0)u[m]=0;

	//	u[m]=abs(matrix[m]/iMaxIm-0.5f)*2;
// 
// 		u[m]=matrix[m]*2.0f/iMaxIm;
// 		if(u[m]>1)	u[m]=1.0f-2.0f*(u[m]-1.0f);//这个地方试是2.5，不是2
// 		if(u[m]<0)	u[m]=0;


		v[m]=u[m];
	}

	imgBufSet=new unsigned char[iDimX*iDimY*iDimZ];
	for(int i=0;i<iDimX*iDimY*iDimZ;i++)
	{		
		imgBufSet[i]=unsigned char(u[i]*255);
	}
	dumpBmp("U_0",imgBufSet,iDimX,iDimY,iDimZ,8);
	delete[] imgBufSet;

	//迭代
	iterationCount=iIterationCountParm;
// 	int depth=iDimZ;
// 	int height=iDimY;
// 	int width=iDimX;
	for (int iter=0;iter<iterationCount;iter++)
	{
		//更新u
		printf("updateInterval:%d\n",iter);
		Backwardx(pxu,dx,iDimX,iDimY,iDimZ);
		Backwardy(pyu,dy,iDimX,iDimY,iDimZ);
		Backwardz(pzu,dz,iDimX,iDimY,iDimZ);

//#pragma ivdep
		for(int i=0;i<volumnSize;i++)
		{
			divp[i]=dx[i]+dy[i]+dz[i];
			term[i]=divp[i]-v[i]/theta;
		}

		Forwardx(term,termx,iDimX,iDimY,iDimZ);
		Forwardy(term,termy,iDimX,iDimY,iDimZ);
		Forwardz(term,termz,iDimX,iDimY,iDimZ);


		float *denom=term;
		/*		float minValue=999.0, maxValue=0.0;*/

		for(int i=0;i<volumnSize;i++)
		{
			denom[i]=sqrt(termx[i]*termx[i]+termy[i]*termy[i]+termz[i]*termz[i]);
			denom[i]=Gb[i]+dt*denom[i];

			pxu[i]=Gb[i]*(pxu[i]+dt*termx[i])/denom[i];
			pyu[i]=Gb[i]*(pyu[i]+dt*termy[i])/denom[i];
			pzu[i]=Gb[i]*(pzu[i]+dt*termz[i])/denom[i];

			u[i]=v[i]-theta*divp[i];

			if(u[i]<0)u[i]=0;
			if(u[i]>1)u[i]=1;

		}


		updateInterval=iNbIterUpdateParm;
		if(iter<1 || (iter+1) % updateInterval==0)
		{

			// RD_MEAN
// 			float MeanIn=0;
// 			float MeanOut=0;
// 			int countIn=0;
// 			int countOut=0;
// 
// 			for(int i=0;i<volumnSize;i++)
// 			{
// 				if(u[i]>=0.5)
// 				{
// 					MeanIn +=pData_temp[i];
// 					countIn++;
// 				}
// 				else{
// 					MeanOut+=pData_temp[i];
// 					countOut++;
// 				}
// 			}
// 			MeanIn/=countIn;
// 			MeanOut/=countOut;
// 
// 			for(int i=0;i<volumnSize;i++)
// 			{
// 				RegionTerm[i]=(pData_temp[i]-MeanIn)*(pData_temp[i]-MeanIn)-
// 					(pData_temp[i]-MeanOut)*(pData_temp[i]-MeanOut);
//			}


 			int NbPtIn=0;
 			int NbPtOut=0;
 			memset(HistIn,0,sizeof(int)*iMaxIm);
 			memset(HistOut,0,sizeof(int)*iMaxIm);
 			int im;
 
 			int m=0;
// #pragma parallel
 			for (int k = 0; k < iDimZ; k++){
 				for (int j = 0; j < iDimY; j++){
 					for (int i = 0; i < iDimX; i++){
 						if(pData_temp[m]>0)
 						{
 							if(u[m]<0.5)
 							{
 								NbPtOut++;
 								im=pData_temp[m];
 								if(im>=iMaxIm)im=iMaxIm-1;
 								HistOut[im]++;
 							}
 							else
 							{
 								NbPtIn++;
 								im=pData_temp[m];
 								if(im>=iMaxIm)im=iMaxIm-1;
 								HistIn[im]++;
 							}
 						}
 						m++;
 					}
 				}
 			}
 
 
// #pragma ivdep
 			for(int i=0;i<iMaxIm;i++)
 			{
 		
 				PdfIn[i]=float(HistIn[i])/float(NbPtIn);
 				PdfOut[i]=float(HistOut[i])/float(NbPtOut);
 			}
 
 			int ct;
 			for(int i=0; i<volumnSize;i++){
 				ct=pData_temp[i];
 				if(ct<0||ct>iMaxIm){
 					/*	printf("ct=%d iMaxIm=%d\n",ct, iMaxIm);*/

 					ct=0;
 				}
 				regionTermIn[i]=PdfIn[ct];
 				regionTermOut[i]=PdfOut[ct];
 			}
//  
//  					float minValue=999.0, maxValue=0.0;
//  					float minValue1=999.0, maxValue1=0.0;
 
 //#pragma ivdep
 			for (int i=0;i<volumnSize;i++)
 			{
 				RegionTerm[i] = regionTermIn[i] - regionTermOut[i];
 
//  				if(RegionTerm[i]>maxValue)maxValue=RegionTerm[i];
//  				if(RegionTerm[i]<minValue)minValue=RegionTerm[i];
//  				if(theta*divp[i]>maxValue1)maxValue1=theta*divp[i];
//  				if(theta*divp[i]<minValue1)minValue1=theta*divp[i];
 			}
			//		printf("theta*divp:min=%f max=%f    RegionTerm: min=%f max=%f\n", minValue1,maxValue1,lambda * theta *minValue, lambda * theta *maxValue);

		}


		//更新v
		for (int i = 0; i < volumnSize; i++)
		{
			v[i] = u[i] + lambda * theta * RegionTerm[i];

			if (v[i] < 0.0 )
				v[i] = 0.0;

			if (v[i] > 1.0 )
				v[i] = 1.0;
		}
		if(iter==1)
		{
			imgBufSet=new unsigned char[iDimX*iDimY*iDimZ];
			for(int i=0;i<iDimX*iDimY*iDimZ;i++)
			{		
				imgBufSet[i]=unsigned char(u[i]*255);
			}
			dumpBmp("U_1",imgBufSet,iDimX,iDimY,iDimZ,8);
			delete[] imgBufSet;
		}
		if(iter==50)
		{
			imgBufSet=new unsigned char[iDimX*iDimY*iDimZ];
			for(int i=0;i<iDimX*iDimY*iDimZ;i++)
			{		
				imgBufSet[i]=unsigned char(u[i]*255);
			}
			dumpBmp("U_50",imgBufSet,iDimX,iDimY,iDimZ,8);
			delete[] imgBufSet;
		}
		if(iter==100)
		{
			imgBufSet=new unsigned char[iDimX*iDimY*iDimZ];
			for(int i=0;i<iDimX*iDimY*iDimZ;i++)
			{		
				imgBufSet[i]=unsigned char(u[i]*255);
			}
			dumpBmp("U_100",imgBufSet,iDimX,iDimY,iDimZ,8);
			delete[] imgBufSet;
		}
		if(iter==150)
		{
			imgBufSet=new unsigned char[iDimX*iDimY*iDimZ];
			for(int i=0;i<iDimX*iDimY*iDimZ;i++)
			{		
				imgBufSet[i]=unsigned char(u[i]*255);
			}
			dumpBmp("U_150",imgBufSet,iDimX,iDimY,iDimZ,8);
			delete[] imgBufSet;
		}
		if(iter==200)
		{
			imgBufSet=new unsigned char[iDimX*iDimY*iDimZ];
			for(int i=0;i<iDimX*iDimY*iDimZ;i++)
			{		
				imgBufSet[i]=unsigned char(u[i]*255);
			}
			dumpBmp("U_200",imgBufSet,iDimX,iDimY,iDimZ,8);
			delete[] imgBufSet;
		}
		if(iter==250)
		{
			imgBufSet=new unsigned char[iDimX*iDimY*iDimZ];
			for(int i=0;i<iDimX*iDimY*iDimZ;i++)
			{		
				imgBufSet[i]=unsigned char(u[i]*255);
			}
			dumpBmp("U_250",imgBufSet,iDimX,iDimY,iDimZ,8);
			delete[] imgBufSet;
		}
	}	

	ippsFree(HistIn);
	ippsFree(HistOut);

	ippsFree(matrix);
	ippsFree(sMatrix);
	ippsFree(dx);
	ippsFree(dy);
	ippsFree(dz);
	ippsFree(gb);
	ippsFree(NormGrad);
	ippsFree(regionTermIn);
	ippsFree(regionTermOut);
	ippsFree(RegionTerm);
	ippsFree(pxu);
	ippsFree(pyu);
	ippsFree(pzu);
	ippsFree(term);
	ippsFree(termx);
	ippsFree(termy);
	ippsFree(termz);
	ippsFree(divp);
	ippsFree(result);
	ippsFree(Gb);

	ippsFree(PdfIn);
	ippsFree(PdfOut);

	//显示U



	imgBufSet=new unsigned char[iDimX*iDimY*iDimZ];
	for(int i=0;i<iDimX*iDimY*iDimZ;i++)
	{		
		imgBufSet[i]=unsigned char(u[i]*255);
	}
	dumpBmp("U",imgBufSet,iDimX,iDimY,iDimZ,8);
	delete[] imgBufSet;

	//将U插值回去
	interpolation2ori(iDim);


	seedtumour[0]-=iDimX_low;
	seedtumour[1]-=iDimY_low;
	seedtumour[2]-=iDimZ_low;
		printf("iDimx:%d,iDimy:%d,iDimz:%d,Seedtumour:{%d,%d,%d}\n",iDimX,iDimY,iDimZ,seedtumour[0],seedtumour[1],seedtumour[2]);

	//肝脏里面就不生长了！！！！
	imgBufSet=new unsigned char[iDimX*iDimY*iDimZ];
		for(int i=0;i<iDimX*iDimY*iDimZ;i++)
		{		
			imgBufSet[i]=unsigned char(u[i]*255);
		}
		dumpBmp("U_before",imgBufSet,iDimX,iDimY,iDimZ,8);
	delete[] imgBufSet;
	region_grow(seedtumour,fReginGrowParm);

	imgBufSet=new unsigned char[iDimX*iDimY*iDimZ];
	for(int i=0;i<iDimX*iDimY*iDimZ;i++)
	{		
		imgBufSet[i]=unsigned char(u[i]*255);
	}
	dumpBmp("U_region",imgBufSet,iDimX,iDimY,iDimZ,8);
	delete[] imgBufSet;

	//对u进行后处理
	fThreU=0.0f;
	printf("fThreU:%f\n",fThreU);
	
	for(int i=0;i<iDimX*iDimY*iDimZ;i++)
	{

		if(u[i]>fThreU)
			pMask_temp[i]=LEISION1;
		else
			pMask_temp[i]=OTHERS;
	}
	//恢复成原来的样子
	iDimX=iDimension[0];
	iDimY=iDimension[1];
	iDimZ=iDimension[2];

	memcpy(pMask,pAllMask,iDimension[0]*iDimension[1]*iDimension[2]*sizeof(char));

	m=0;

	for(int i=iDimZ_low;i<=iDimZ_high;i++)
	{
		for(int j=iDimY_low;j<=iDimY_high;j++)
		{
			for(int k=iDimX_low;k<=iDimX_high;k++)
			{
				index=i*iDimension[0]*iDimension[1]+j*iDimension[0]+k;
				//pMask[index]=OTHERS;

				if(pAllMask[index]==LIVER_8SEGMENT_WHOLE)
				{
				//	pMask[index]=LIVER_8SEGMENT_WHOLE;
					if(pMask_temp[m]==LEISION1)
						{
							pMask[index]=LEISION1;
					     }

				}

				m++;
			
			}
		}
	}
	imgBufSet=new unsigned char[iDimX*iDimY*iDimZ];
	for(int i=0;i<iDimX*iDimY*iDimZ;i++)
	{	
		imgBufSet[i]=0;
		if(pMask[i]==LEISION1)imgBufSet[i]=100;
		if(pMask[i]==LIVER_8SEGMENT_WHOLE)imgBufSet[i]=255;
		if(pMask[i]==OTHERS)imgBufSet[i]=0;
		
	}
	dumpBmp("result",imgBufSet,iDimX,iDimY,iDimZ,8);
	delete[] imgBufSet;

	ippsFree(u);
	ippsFree(v);
	delete[] pMask_temp;
}

void SegFunction::get_tumour_Features(const short*pData_base, const int *iDimension,const float *fSpace,const char *pMask,float *fFeatures)
{
	//fFeatures[0]:用于记录肿瘤最大直径
	//fFeatures[1]:用于记录肿瘤体积
	//fFeatures[2]:用于记录肿瘤平均ct值
	float volumeNum=0;
	float ave=0;


	int x_low=iDimension[0];
	int x_high=0;
	int y_low=iDimension[1];
	int y_high=0;
	int z_low=iDimension[2];
	int z_high=0;

	int i,j,k;
	int index;
	int pageSize=iDimension[0]*iDimension[1];

	//ture为边界，false为空。
	bool *tempChar=new bool[iDimension[0]*iDimension[1]*iDimension[2]];
    memset(tempChar,false,iDimension[0]*iDimension[1]*iDimension[2]*sizeof(bool));
	int pointNum=0;//边界点个数

	for(i=0;i<iDimension[2];i++)
	{
		for(j=0;j<iDimension[1];j++)
		{
			for(k=0;k<iDimension[0];k++)
			{
				index=i*iDimension[1]*iDimension[0]+j*iDimension[0]+k;

				if(pMask[index]==LEISION1)
				{
					volumeNum++;

					if(k<x_low)x_low=k;
				    if(k>x_high)x_high=k;
				    if(j<y_low)y_low=j;
				    if(j>y_high)y_high=j;
				    if(i<z_low)z_low=i;
				    if(i>z_high)z_high=i;
					ave+=pData_base[index];
					//判断边界点
					if(i==0||i==iDimension[2]-1||j==0||j==iDimension[1]-1||k==0||k==iDimension[0]-1)
					{
						tempChar[index]=true;
						pointNum++;
					}
					else
					{
						//判断周围八领域是否都为满的。
						int sum=0;
						for(int ii=-1;ii<=1;ii++)
						{
							sum+=pMask[index+ii];
							sum+=pMask[index+iDimension[0]*ii];
							sum+=pMask[index+pageSize*ii];
						}
						if(sum<LEISION1*27)
						{
							tempChar[index]=true;
							pointNum++;

						}
					}
				}
			}
		}
	}

	ave=ave/volumeNum;

	fFeatures[0]=0;
	fFeatures[1]=volumeNum*fSpace[0]*fSpace[1]*fSpace[2];
	fFeatures[2]=ave;

	TPoint *ply=new TPoint[pointNum];
	int cnt=0;
	for( i=0;i<iDimension[2];i++)
	{
	    for(j=0;j<iDimension[1];j++)
		{
			for( k=0;k<iDimension[0];k++)
			{
				if(tempChar[i*pageSize+j*iDimension[0]+k])
				{
					ply[cnt].x=(float)k;
					ply[cnt].y=(float)j;
					ply[cnt].z=(float)i;
					cnt++;
				}
			}
		}
	}
	printf("pointNUm:%d, cnt:%d\n",pointNum,cnt);

	Hull3D hull(ply,pointNum);
	hull.construct();
	//fFeatures[0]=hull.diameter()*fSpace[0]*fSpace[1]*fSpace[2];
	fFeatures[0]=hull.diameter();
	printf("diameter: %.4f\n,volume: %.4f\n, Ct(avg) :%.4f\n",fFeatures[0],fFeatures[1],fFeatures[2]);


}

//采用给定点来进行八段分割  文档中第一种方案
bool SegFunction::seg_mask_8(const char *pAllMask,const int* vein,const int *veinR,const int *veinM, const int *portal, const int* portalL, const int portalLineL,const int portalLineR,char *pMask,const int *iDim)
{
	printf("vein: (%d,%d,%d)\n",vein[0],vein[1],vein[2]);
	printf("veinR: (%d,%d,%d)\n",veinR[0],veinR[1],veinR[2]);
	printf("veinM: (%d,%d,%d)\n",veinM[0],veinM[1],veinM[2]);
	printf("portal: (%d,%d,%d)\n",portal[0],portal[1],portal[2]);
	printf("portalL: (%d,%d,%d)\n",portalL[0],portalL[1],portalL[2]);

	printf("portalLineL: %d\n",portalLineL);
	printf("portalLineR: %d\n",portalLineR);

	seg_mask_8_4(pAllMask,vein,portalL,portal,pMask,iDim);
	//writeData(pMask,"F://CentreLine2//1213-5//WangChaofeng//seg_1.raw",iDim);
	seg_mask_8_1(vein,veinM,portal,pMask,iDim);
	//writeData(pMask,"F://CentreLine2//1213-5//WangChaofeng//seg_2.raw",iDim);
	seg_mask_8_2(vein,veinR,portal,pMask,iDim);
	//writeData(pMask,"F://CentreLine2//1213-5//WangChaofeng//seg_3.raw",iDim);
	seg_mask_8_3(portalLineR,pMask,iDim);
	//writeData(pMask,"F://CentreLine2//1213-5//WangChaofeng//seg_4.raw",iDim);
	seg_mask_8_5(portalLineL, pMask,iDim);
	//writeData(pMask,"F://CentreLine2//1213-5//WangChaofeng//seg_5.raw",iDim);
	return true;
}
bool SegFunction::seg_mask_8_centerline(const char *centerlineName,int* vein, int *veinR, int *veinM,  int* portal,  int* portalL, int* portalLineL,int* portalLineR,int *point)
{
	//获取中心线文件，并生成中心线点

	int portalR[3];
	int veinL[3];

	FILE *fp;
	int error=fopen_s(&fp,centerlineName,"rb");
	if(error!=0)return false;


	//规定指针位置总是相对于文件的起始位置
	int flag=0;
	int count;
	float  radius;
	bool bruchflag=false;//没有第三支是flase，有是true

	char c;
	int line=0;//行号

	while((c=(char)fgetc(fp))!=EOF)
	{
		fseek(fp,-1,SEEK_CUR);
		fscanf_s(fp,"%d",&flag);
		if(flag==0)break;
		fscanf_s(fp,"%d%f",&count,&radius);
		//printf("flag : %d count :%d  radius: %f\n",flag,count, radius);
		int sum;
		int x=0,y=0,z=0;
		//往下读count行
		switch(flag)
		{
		case 11://门静脉
			line=0;
			while(line!=count)
			{
				if((c=(char)fgetc(fp))=='\n')
					line++;
			}
			fscanf_s(fp,"%d%d%d",&portal[0],&portal[1],&portal[2]);
			printf("11: %d,%d,%d,\n",portal[0],portal[1],&portal[2]);
			break;

		case 12://肝静脉
			line=0;
			while(line!=count)
			{
				if((c=(char)fgetc(fp))=='\n')
					line++;
			}
			fscanf_s(fp,"%d%d%d",&vein[0],&vein[1],&vein[2]);
			printf("12: %d,%d,%d\n",vein[0],vein[1],vein[2]); 
			break;

 		case 112://肝静脉右支：
 			line=0;
 			while(line!=count)
 			{
 				if((c=(char)fgetc(fp))=='\n')
 					line++;
 			}
 			fscanf_s(fp,"%d%d%d",&veinR[0],&veinR[1],&veinR[2]);
 
 			printf("112: %d,%d,%d\n",veinR[0],veinR[1],veinR[2]);
 			break;

		case 212://肝中静脉
			line=0;
			while(line!=count)
			{
				if((c=(char)fgetc(fp))=='\n')
					line++;
			}
			fscanf_s(fp,"%d%d%d",&veinM[0],&veinM[1],&veinM[2]);

			printf("212: %d,%d,%d\n",veinM[0],veinM[1],veinM[2]);
			break;

		case 312://肝静脉左支
			line=0;
			while(line!=count)
			{
				if((c=(char)fgetc(fp))=='\n')
					line++;
			}
			fscanf_s(fp,"%d%d%d",&veinL[0],&veinL[1],&veinL[2]);
			bruchflag=true;
			printf("312: %d,%d,%d\n",veinL[0],veinL[1],veinL[2]);
			break;
		case 211://门静脉左支
			line=0;
			sum=0;
			while(line!=count)
			{
				fscanf_s(fp,"%d%d%d",&x,&y,&z);
				//		printf("211: %d,%d,%d\n",x,y,z);
				sum+=z;
				line++;
			}
			//fscanf(fp,"%d%d%d",&portalR[0],&portalR[1],&portalR[2]);
			portalL[0]=x;
			portalL[1]=y;
			portalL[2]=z;

			*portalLineL=sum/count;
			//	printf("portalRLine: %d\n",portalRLine);
			break;
		case 111://门静脉右支
			line=0;
			sum=0;
			while(line!=count)
			{
				fscanf_s(fp,"%d%d%d",&x,&y,&z);
				//		printf("111: %d,%d,%d\n",x,y,z);
				sum+=z;
				line++;
			}
			portalR[0]=x;
			portalR[1]=y;
			portalR[2]=z;

			*portalLineR=sum/count;
			//		printf("portalLine:%d\n",portalLLine);
			break;
		default:
			line=0;
			while(line<=count)
			{
				if((c=(char)fgetc(fp))=='\n')
					line++;
			}
			break;
		}
	}
	//判断左右支
	int a[3]={0};
	int t=0;
	if(portalL[1]>portalR[1])
	{
		//左右支反了
		printf("change portal L&R\n");
		a[0]=portalR[0];
		a[1]=portalR[1];
		a[2]=portalR[2];

		t=*portalLineR;

		portalR[0]=portalL[0];
		portalR[1]=portalL[1];
		portalR[2]=portalL[2];
		*portalLineR=*portalLineL;

		portalL[0]=a[0];
		portalL[1]=a[1];
		portalL[2]=a[2];

		*portalLineL=t;
	}


	//判断静脉左右支
	int plane[4];
	generate_plane_3point(vein,portal,portalL,plane);
	int aim[3];
	for(int i=0;i<3;i++)
	{
		aim[i]=vein[i]-portal[i];
	}
	int planeVein[3][4]={0};//生成三个平面
	if(bruchflag==false)//只有两支
	{
		printf("only have 2 bruch!");
		generate_plane_3point(vein,portal,veinR,planeVein[0]);
		generate_plane_3point(vein,portal,veinM,planeVein[1]);

		float cosValue1,cosValue2;
		bool b1,b2;
		b1=find_place(plane,planeVein[0],aim,cosValue1);
		b2=find_place(plane,planeVein[1],aim,cosValue2);
		printf("\n cos1:%f,cos2:%f",cosValue1,cosValue2);

		if(b1)printf("b1:true ");else printf("b1: false ");
		if(b2)printf("b2:true\n");else printf("b2: false\n");

		if(cosValue1<cosValue2)
		{

			printf("veinM: %d,%d,%d\n",veinM[0],veinM[1],veinM[2]);
			printf("veinR: %d,%d,%d\n",veinR[0],veinR[1],veinR[2]);
		}
		else
		{
			swapPoint(veinM,veinR);
			printf("veinM: %d,%d,%d\n",veinM[0],veinM[1],veinM[2]);
			printf("veinR: %d,%d,%d\n",veinR[0],veinR[1],veinR[2]);
		}
	}

	if(bruchflag==true)//有三支
	{
		generate_plane_3point(vein,portal,veinR,planeVein[0]);
		generate_plane_3point(vein,portal,veinM,planeVein[1]);
		generate_plane_3point(vein,portal,veinL,planeVein[2]);
		int p[3][3]={0};
		copypoint(p[0],veinR);
		copypoint(p[1],veinM);
		copypoint(p[2],veinL);


		int a[3]={0};
		float cosValue[3];
		for(int i=0;i<3;i++)
		{
			if(find_place(plane,planeVein[i],aim,cosValue[i]))
				a[i]=1;
			else
				a[i]=-1;
			printf("\n cos%d: %f ",i,cosValue[i]);
			if(a[i]>0)printf("true\n");else printf("flase\n");
		}
		int veinflag=a[0]+a[1]+a[2];
		if(abs(veinflag)==1)
		{
		int i=0;
		for(i=0;i<3;i++)
		{
			if(a[i]!=veinflag)break;
		}
		int b=(i+1)%3;//取另外两个符号相同的
		int c=(i+2)%3;
		if(cosValue[b]<cosValue[c])
		{
			swapPoint(veinR,p[b]);
			swapPoint(veinM,p[c]);

		}
		else
		{
			swapPoint(veinM,p[b]);
			swapPoint(veinR,p[c]);
		}
		}
		if(abs(veinflag)==3)
		{
			//最大的是右，其次的是中
			int i=0;
			int j=0;
			float temp=-1;
			//找最大值
			for(i=0;i<3;i++)
			{
				if(cosValue[i]>temp)
				{
				   temp=cosValue[i];
					j=i;
				}
			}

			swapPoint(veinR,p[j]);

			int b=(j+1)%3;//取另外两个符号相同的
			int c=(j+2)%3;
			if(cosValue[b]<cosValue[c])
			{
				swapPoint(veinR,p[b]);
				swapPoint(veinM,p[c]);

			}
			else
			{
				swapPoint(veinM,p[b]);
				swapPoint(veinR,p[c]);
			}
			

		
		}

	}
	if(point!=NULL){
	copypoint(&point[0],vein);
	copypoint(&point[3],portal);
	copypoint(&point[6],veinM);

	copypoint(&point[9],vein);
	copypoint(&point[12],portal);
	copypoint(&point[15],veinR);
	
	for(int i=18;i<26;i++)point[i]=0;
	point[26]=*portalLineR;

	copypoint(&point[27],vein);
	copypoint(&point[30],portal);
	copypoint(&point[33],portalL);

	for(int i=36;i<44;i++)point[i]=0;
	point[44]=*portalLineL;
	}

	veinPoint[0]=vein[0];
	veinPoint[1]=vein[1];
	veinPoint[2]=vein[2];
	portalPoint[0]=portal[0];
	portalPoint[1]=portal[1];
	portalPoint[2]=portal[2];
	//vein 肝静脉第一个分叉点  veinM肝中静脉第一个分叉点   portal门静脉第一个分叉点
	//centrePoint[0]=(vein[0]+portal[0])/2;
	//centrePoint[1]=(vein[0]+portal[0])/2;
	//centrePoint[2]=(vein[0]+portal[0])/2;
	//searchLen=sqrt(double((vein[0]-portal[0])*(vein[0]-portal[0])+(vein[1]-portal[1])*(vein[1]-portal[1])+(vein[2]-portal[2])*(vein[2]-portal[2])));
	return true;
}
//void SegFunction::seg_mask_8_1(const char *pAllMask,const int* vein,const int *veinM,const int *portal,char *pMask,const int *iDim)
//{
//	int plane[4];
//	generate_plane_3point(vein,portal,veinM,plane);
//	printf("1: plane %dx+ %dy+ %dz+ %d =0\n",plane[0],plane[1],plane[2],plane[3]);
//	int m=0;
//	for(int i=0;i<iDim[2];i++)
//	{
//		for(int j=0;j<iDim[1];j++)
//		{
//			for(int k=0;k<iDim[0];k++)
//			{
//				m=i*iDim[0]*iDim[1]+j*iDim[0]+k;
//				if(pAllMask[m]==LIVER_8SEGMENT_WHOLE)
//				{
//					int ans=k*plane[0]+j*plane[1]+i*plane[2]+plane[3];//ans=Ax+By+Cz+D;
//					if(ans<0)
//						pMask[m]=LIVER_8SEGMENT_PART2;
//					else
//						pMask[m]=LIVER_8SEGMENT_PART1;
//				}
//				else
//				{
//					pMask[m]=0;
//				}
//			}
//		}
//	}
//}
//void SegFunction::seg_mask_8_2(const int* vein,const int *veinR,const int *portal,char *pMask,const int *iDim)
//{
//	int plane[4];
//	generate_plane_3point(vein,portal,veinR,plane);
//	printf("\n2: plane %dx+ %dy+ %dz+ %d =0\n",plane[0],plane[1],plane[2],plane[3]);
//	int m=0;
//	for(int i=0;i<iDim[2];i++)
//	{
//		for(int j=0;j<iDim[1];j++)
//		{
//			for(int k=0;k<iDim[0];k++)
//			{
//				m=i*iDim[0]*iDim[1]+j*iDim[0]+k;
//				if(pMask[m]==LIVER_8SEGMENT_PART1)
//				{
//					int ans=k*plane[0]+j*plane[1]+i*plane[2]+plane[3];//ans=Ax+By+Cz+D;
//					if(ans<0)
//						pMask[m]=LIVER_8SEGMENT_PART8;
//					else
//						pMask[m]=LIVER_8SEGMENT_PART7;
//				}
//				/*	m++;*/
//			}
//		}
//	}
//	
//}
//void SegFunction::seg_mask_8_3(const int portalLineR,char *pMask,const int *iDim)
//{
//	int plane[4]={0};
//	plane[2]=1;
//	plane[3]=-portalLineR;
//	int m=0;
//	printf("\n3: plane %dx+ %dy+ %dz+ %d =0\n",plane[0],plane[1],plane[2],plane[3]);
//	for(int i=0;i<iDim[2];i++)
//	{
//		for(int j=0;j<iDim[1];j++)
//		{
//			for(int k=0;k<iDim[0];k++)
//			{
//				m=i*iDim[0]*iDim[1]+j*iDim[0]+k;
//				if(pMask[m]==LIVER_8SEGMENT_PART7||pMask[m]==LIVER_8SEGMENT_PART8)
//				{
//					int ans=k*plane[0]+j*plane[1]+i*plane[2]+plane[3];//ans=Ax+By+Cz+D;
//					if(ans>0)
//					{
//						if(pMask[m]==LIVER_8SEGMENT_PART7)pMask[m]=LIVER_8SEGMENT_PART7;
//						if(pMask[m]==LIVER_8SEGMENT_PART8)pMask[m]=LIVER_8SEGMENT_PART8;
//					}
//					else
//					{
//						if(pMask[m]==LIVER_8SEGMENT_PART7)pMask[m]=LIVER_8SEGMENT_PART6;
//						if(pMask[m]==LIVER_8SEGMENT_PART8)pMask[m]=LIVER_8SEGMENT_PART5;
//					}
//				}
//				// 
//				// 				m++;
//			}
//		}
//	}
//}
//void SegFunction::seg_mask_8_4(const int* vein,const int *portalR,const int *portal,char *pMask,const int *iDim)
//{
//	int plane[4];
//	generate_plane_3point(vein,portal,portalR,plane);
//
//	printf("4: plane %dx+ %dy+ %dz+ %d =0\n",plane[0],plane[1],plane[2],plane[3]);
//	if(plane[0]>0)
//	{
//		plane[0]=-plane[0];
//		plane[1]=-plane[1];
//		plane[2]=-plane[2];
//		plane[3]=-plane[3];
//	}
//	int m=0;
//	for(int i=0;i<iDim[2];i++)
//	{
//		for(int j=0;j<iDim[1];j++)
//		{
//			for(int k=0;k<iDim[0];k++)
//			{
//				m=i*iDim[0]*iDim[1]+j*iDim[0]+k;
//				if(pMask[m]==LIVER_8SEGMENT_PART2)
//				{
//					int ans=k*plane[0]+j*plane[1]+i*plane[2]+plane[3];//ans=Ax+By+Cz+D;
//					if(ans<0)
//					{
//						pMask[m]=LIVER_8SEGMENT_PART2;
//
//					}
//					else
//					{
//						pMask[m]=LIVER_8SEGMENT_PART4;
//					}
//				}
//
//				/*	m++;*/
//			}
//		}
//	}
//}
//void SegFunction::seg_mask_8_5(const int portalLineL, char *pMask,const int *iDim)
//{
//	int plane[4]={0};
//	plane[2]=1;
//	plane[3]=-portalLineL;
//	printf("\n5: plane %dx+ %dy+ %dz+ %d =0\n",plane[0],plane[1],plane[2],plane[3]);
//	int m=0;
//	for(int i=0;i<iDim[2];i++)
//	{
//		for(int j=0;j<iDim[1];j++)
//		{
//			for(int k=0;k<iDim[0];k++)
//			{ 
//				m=i*iDim[0]*iDim[1]+j*iDim[0]+k;
//				if(pMask[m]==LIVER_8SEGMENT_PART2)
//				{
//					int ans=k*plane[0]+j*plane[1]+i*plane[2]+plane[3];//ans=Ax+By+Cz+D;
//					if(ans>0)
//					{
//						pMask[m]=LIVER_8SEGMENT_PART2;
//
//					}
//					else
//					{
//						pMask[m]=LIVER_8SEGMENT_PART3;
//					}
//				}
//
//				/*	m++;*/
//			}
//		}
//	}
//}

void SegFunction::seg_mask_8_4(const char *pAllMask,const int* vein,const int *portalR,const int *portal,char *pMask,const int *iDim)
{
	int plane[4];
	generate_plane_3point(vein,portal,portalR,plane);

	printf("4: plane %dx+ %dy+ %dz+ %d =0\n",plane[0],plane[1],plane[2],plane[3]);
	if(plane[0]>0)
	{
		plane[0]=-plane[0];
		plane[1]=-plane[1];
		plane[2]=-plane[2];
		plane[3]=-plane[3];
	}
	int m=0;
	for(int i=0;i<iDim[2];i++)
	{
		for(int j=0;j<iDim[1];j++)
		{
			for(int k=0;k<iDim[0];k++)
			{
				m=i*iDim[0]*iDim[1]+j*iDim[0]+k;
				if(pAllMask[m]==LIVER_8SEGMENT_WHOLE)
				{
					int ans=k*plane[0]+j*plane[1]+i*plane[2]+plane[3];//ans=Ax+By+Cz+D;
					if(ans<0)
					{
						pMask[m]=LIVER_8SEGMENT_PART2; //认为小于0的是右边

					}
					else
					{
						pMask[m]=LIVER_8SEGMENT_PART1;
					}
				}
				else
				{
					pMask[m]=0;
				}
				/*	m++;*/
			}
		}
	}
}
void SegFunction::seg_mask_8_1(const int* vein,const int *veinM,const int *portal,char *pMask,const int *iDim)
{
	int plane[4];
	generate_plane_3point(vein,portal,veinM,plane);
	printf("1: plane %dx+ %dy+ %dz+ %d =0\n",plane[0],plane[1],plane[2],plane[3]);
	int m=0;
	for(int i=0;i<iDim[2];i++)
	{
		for(int j=0;j<iDim[1];j++)
		{
			for(int k=0;k<iDim[0];k++)
			{
				m=i*iDim[0]*iDim[1]+j*iDim[0]+k;
				if(pMask[m]==LIVER_8SEGMENT_PART1)
				{
					int ans=k*plane[0]+j*plane[1]+i*plane[2]+plane[3];//ans=Ax+By+Cz+D;
					if(ans<0)
						pMask[m]=LIVER_8SEGMENT_PART4;
					else
						pMask[m]=LIVER_8SEGMENT_PART1;
				}
				/*else
				{
					pMask[m]=0;
				}*/
			}
		}
	}
}
void SegFunction::seg_mask_8_2(const int* vein,const int *veinR,const int *portal,char *pMask,const int *iDim)
{
	int plane[4];
	generate_plane_3point(vein,portal,veinR,plane);
	printf("\n2: plane %dx+ %dy+ %dz+ %d =0\n",plane[0],plane[1],plane[2],plane[3]);
	int m=0;
	for(int i=0;i<iDim[2];i++)
	{
		for(int j=0;j<iDim[1];j++)
		{
			for(int k=0;k<iDim[0];k++)
			{
				m=i*iDim[0]*iDim[1]+j*iDim[0]+k;
				if(pMask[m]==LIVER_8SEGMENT_PART1)
				{
					int ans=k*plane[0]+j*plane[1]+i*plane[2]+plane[3];//ans=Ax+By+Cz+D;
					if(ans<0)
						pMask[m]=LIVER_8SEGMENT_PART8;
					else
						pMask[m]=LIVER_8SEGMENT_PART7;
				}
				/*	m++;*/
			}
		}
	}
	
}
void SegFunction::seg_mask_8_3(const int portalLineR,char *pMask,const int *iDim)
{
	int plane[4]={0};
	plane[2]=1;
	plane[3]=-portalLineR;
	int m=0;
	printf("\n3: plane %dx+ %dy+ %dz+ %d =0\n",plane[0],plane[1],plane[2],plane[3]);
	for(int i=0;i<iDim[2];i++)
	{
		for(int j=0;j<iDim[1];j++)
		{
			for(int k=0;k<iDim[0];k++)
			{
				m=i*iDim[0]*iDim[1]+j*iDim[0]+k;
				if(pMask[m]==LIVER_8SEGMENT_PART7||pMask[m]==LIVER_8SEGMENT_PART8)
				{
					int ans=k*plane[0]+j*plane[1]+i*plane[2]+plane[3];//ans=Ax+By+Cz+D;
					if(ans>0)
					{
						if(pMask[m]==LIVER_8SEGMENT_PART7)pMask[m]=LIVER_8SEGMENT_PART7;
						if(pMask[m]==LIVER_8SEGMENT_PART8)pMask[m]=LIVER_8SEGMENT_PART8;
					}
					else
					{
						if(pMask[m]==LIVER_8SEGMENT_PART7)pMask[m]=LIVER_8SEGMENT_PART6;
						if(pMask[m]==LIVER_8SEGMENT_PART8)pMask[m]=LIVER_8SEGMENT_PART5;
					}
				}
				// 
				// 				m++;
			}
		}
	}
}

//
//void SegFunction::Tran_seg_mask_8_3(const int portalLineR,char *pMask,const int *iDim,const int *iTranOriginal)
//{
//	int plane[4]={0};
//	plane[2]=1;
//	plane[3]=-portalLineR;
//	int m=0;
//	printf("\n3: plane %dx+ %dy+ %dz+ %d =0\n",plane[0],plane[1],plane[2],plane[3]);
//	for(int i=0;i<iDim[2];i++)
//	{
//		for(int j=0;j<iDim[1];j++)
//		{
//			for(int k=0;k<iDim[0];k++)
//			{
//				m=i*iDim[0]*iDim[1]+j*iDim[0]+k;
//				if(pMask[m]==LIVER_8SEGMENT_PART7||pMask[m]==LIVER_8SEGMENT_PART8)
//				{
//					int ans=k*plane[0]+j*plane[1]+i*plane[2]+plane[3];//ans=Ax+By+Cz+D;
//					if(ans>0)
//					{
//						if(pMask[m]==LIVER_8SEGMENT_PART7)pMask[m]=LIVER_8SEGMENT_PART7;
//						if(pMask[m]==LIVER_8SEGMENT_PART8)pMask[m]=LIVER_8SEGMENT_PART8;
//					}
//					else
//					{
//						if(pMask[m]==LIVER_8SEGMENT_PART7)pMask[m]=LIVER_8SEGMENT_PART6;
//						if(pMask[m]==LIVER_8SEGMENT_PART8)pMask[m]=LIVER_8SEGMENT_PART5;
//					}
//				}
//				// 
//				// 				m++;
//			}
//		}
//	}
//}


void SegFunction::seg_mask_8_5(const int portalLineL, char *pMask,const int *iDim)
{
	int plane[4]={0};
	plane[2]=1;
	plane[3]=-portalLineL;
	printf("\n5: plane %dx+ %dy+ %dz+ %d =0\n",plane[0],plane[1],plane[2],plane[3]);
	int m=0;
	for(int i=0;i<iDim[2];i++)
	{
		for(int j=0;j<iDim[1];j++)
		{
			for(int k=0;k<iDim[0];k++)
			{ 
				m=i*iDim[0]*iDim[1]+j*iDim[0]+k;
				if(pMask[m]==LIVER_8SEGMENT_PART2)
				{
					int ans=k*plane[0]+j*plane[1]+i*plane[2]+plane[3];//ans=Ax+By+Cz+D;
					if(ans>0)
					{
						pMask[m]=LIVER_8SEGMENT_PART2;

					}
					else
					{
						pMask[m]=LIVER_8SEGMENT_PART3;
					}
				}

				/*	m++;*/
			}
		}
	}
}

bool SegFunction::seg_mask_8(const char *pAllMask, const vector<vector<TPoint>> &vCenterlines,const vector<TPoint> &vHeader, char *pMask,const int *iDim)
{
	int vein[3]={0};
	int veinM[3]={0};
	int veinR[3]={0};
	int portal[3]={0};
	int portalL[3]={0};

	int portalLineR=0;
	int portalLineL=0;

	int portalR[3]={0};
	int veinL[3]={0};

	bool bruchflag=false;

	if(vCenterlines.size()!=vHeader.size())
	{
		printf("the size is not equal!!!");
			return false;
	}
	int lineNum=int (vCenterlines.size());
	for(int i=0;i<lineNum;i++)
	{
		int flag=int(vHeader[i].x);
		int n=int(vCenterlines[i].size())-1;
		float sum=0;
		switch(flag)
		{

		case 11://门静脉	
			portal[0]=int(vCenterlines[i][n].x);
     		portal[1]=int(vCenterlines[i][n].y);
			portal[2]=int(vCenterlines[i][n].z);
			break;
		case 12://肝静脉
			vein[0]=int(vCenterlines[i][n].x);
			vein[1]=int(vCenterlines[i][n].y);
			vein[2]=int(vCenterlines[i][n].z);
			break;

		case 112://肝静脉右支：
			veinR[0]=int(vCenterlines[i][n].x);
			veinR[1]=int(vCenterlines[i][n].y);
			veinR[2]=int(vCenterlines[i][n].z);
			break;

		case 212://肝中静脉
			veinM[0]=int(vCenterlines[i][n].x);
			veinM[1]=int(vCenterlines[i][n].y);
			veinM[2]=int(vCenterlines[i][n].z);
			break;

		case 312://肝静脉左支
			veinL[0]=int(vCenterlines[i][n].x);
			veinL[1]=int(vCenterlines[i][n].y);
			veinL[2]=int(vCenterlines[i][n].z);
			bruchflag=true;

			break;

		case 211://门静脉左支
			portalL[0]=int(vCenterlines[i][n].x);
			portalL[1]=int(vCenterlines[i][n].y);
			portalL[2]=int(vCenterlines[i][n].z);
		    sum=0;
			for(int j=0;j<=n;j++)
			sum+=vCenterlines[i][j].z;
			portalLineL=int(sum/(n+1));
			break;
		case 111://门静脉右支
			portalR[0]=int(vCenterlines[i][n].x);
			portalR[1]=int(vCenterlines[i][n].y);
			portalR[2]=int(vCenterlines[i][n].z);
		    sum=0;
			for(int j=0;j<=n;j++)
				sum+=vCenterlines[i][j].z;
			portalLineR=int(sum/(n+1));
			break;
		default:
		break;
		}
	}
	//判断左右支
	int a[3]={0};
	int t=0;
	if(portalL[1]>portalR[1])
	{
		//左右支反了
		printf("change portal L&R\n");
		a[0]=portalR[0];
		a[1]=portalR[1];
		a[2]=portalR[2];

		t=portalLineR;

		portalR[0]=portalL[0];
		portalR[1]=portalL[1];
		portalR[2]=portalL[2];
		portalLineR=portalLineL;

		portalL[0]=a[0];
		portalL[1]=a[1];
		portalL[2]=a[2];

		portalLineL=t;
	}


	//判断静脉左右支
	int plane[4];
	generate_plane_3point(vein,portal,portalL,plane);
	int aim[3];
	for(int i=0;i<3;i++)
	{
		aim[i]=vein[i]-portal[i];
	}
	int planeVein[3][4]={0};//生成三个平面
	if(bruchflag==false)//只有两支
	{
		printf("only have 2 bruch!");
		generate_plane_3point(vein,portal,veinR,planeVein[0]);
		generate_plane_3point(vein,portal,veinM,planeVein[1]);

		float cosValue1,cosValue2;
		bool b1,b2;
		b1=find_place(plane,planeVein[0],aim,cosValue1);
		b2=find_place(plane,planeVein[1],aim,cosValue2);
		printf("\n cos1:%f,cos2:%f",cosValue1,cosValue2);

		if(b1)printf("b1:true ");else printf("b1: false ");
		if(b2)printf("b2:true\n");else printf("b2: false\n");

		if(cosValue1<cosValue2)
		{

			printf("veinM: %d,%d,%d\n",veinM[0],veinM[1],veinM[2]);
			printf("veinR: %d,%d,%d\n",veinR[0],veinR[1],veinR[2]);
		}
		else
		{
			swapPoint(veinM,veinR);
			printf("veinM: %d,%d,%d\n",veinM[0],veinM[1],veinM[2]);
			printf("veinR: %d,%d,%d\n",veinR[0],veinR[1],veinR[2]);
		}
	}

	if(bruchflag==true)//有三支
	{
		generate_plane_3point(vein,portal,veinR,planeVein[0]);
		generate_plane_3point(vein,portal,veinM,planeVein[1]);
		generate_plane_3point(vein,portal,veinL,planeVein[2]);
		int p[3][3]={0};
		copypoint(p[0],veinR);
		copypoint(p[1],veinM);
		copypoint(p[2],veinL);


		int a[3]={0};
		float cosValue[3];
		for(int i=0;i<3;i++)
		{
			if(find_place(plane,planeVein[i],aim,cosValue[i]))
				a[i]=1;
			else
				a[i]=-1;
			printf("\n cos%d: %f ",i,cosValue[i]);
			if(a[i]>0)printf("true\n");else printf("flase\n");
		}
		int veinflag=a[0]+a[1]+a[2];
		if(abs(veinflag)==1)
		{
			int i=0;
			for(i=0;i<3;i++)
			{
				if(a[i]!=veinflag)break;
			}
			int b=(i+1)%3;//取另外两个符号相同的
			int c=(i+2)%3;
			if(cosValue[b]<cosValue[c])
			{
				swapPoint(veinR,p[b]);
				swapPoint(veinM,p[c]);

			}
			else
			{
				swapPoint(veinM,p[b]);
				swapPoint(veinR,p[c]);
			}
		}
		if(abs(veinflag)==3)
		{
			//最大的是右，其次的是中
			int i=0;
			int j=0;
			float temp=-1;
			//找最大值
			for(i=0;i<3;i++)
			{
				if(cosValue[i]>temp)
				{
					temp=cosValue[i];
					j=i;
				}
			}

			swapPoint(veinR,p[j]);

			int b=(j+1)%3;//取另外两个符号相同的
			int c=(j+2)%3;
			if(cosValue[b]<cosValue[c])
			{
				swapPoint(veinR,p[b]);
				swapPoint(veinM,p[c]);

			}
			else
			{
				swapPoint(veinM,p[b]);
				swapPoint(veinR,p[c]);
			}



		}

	}
	//vein 肝静脉第一个分叉点  veinM肝中静脉第一个分叉点   portal门静脉第一个分叉点
	centrePoint[0]=(vein[0]+portal[0])/2;
	centrePoint[1]=(vein[0]+portal[0])/2;
	centrePoint[2]=(vein[0]+portal[0])/2;
	searchLen=sqrt(double((vein[0]-portal[0])*(vein[0]-portal[0])+(vein[1]-portal[1])*(vein[1]-portal[1])+(vein[2]-portal[2])*(vein[2]-portal[2])));
	seg_mask_8_4(pAllMask,vein,portalL,portal,pMask,iDim);
	seg_mask_8_1(vein,veinM,portal,pMask,iDim);
	seg_mask_8_2(vein,veinR,portal,pMask,iDim);
	seg_mask_8_3(portalLineR,pMask,iDim);
	seg_mask_8_5(portalLineL, pMask,iDim);

	return true;

}

void SegFunction::smooth(int model)
{
	//模板大小
	//x方向
	int *pVal=new int[iDimX*iDimY*iDimZ];
	int *pValTemp=new int[iDimX*iDimY*iDimZ];
	int thre=(2*model+1)*((2*model+1))*((2*model+1))/2;
	memset(pVal,0,sizeof(int)*iDimX*iDimY*iDimZ);
	memset(pValTemp,0,sizeof(int)*iDimX*iDimY*iDimZ);
	for(int i=model;i<iDimZ-model;i++)
	{
		for(int j=model;j<iDimY-model;j++)
		{
			for(int k=model;k<iDimX-model;k++)
			{
				int count=0;
				for(int m=-model;m<=model;m++)
				{
					int t=i*iDimX*iDimY+j*iDimX+(k+m);
					if(pMask_temp[t]==LIVER_8SEGMENT_WHOLE)count++;
				}
				pVal[i*iDimX*iDimY+j*iDimX+k]=count;
			}
		}
	}

	//Y方向
	for(int i=model;i<iDimZ-model;i++)
	{
		for(int j=model;j<iDimY-model;j++)
		{
			for(int k=model;k<iDimX-model;k++)
			{
				int count=0;
				for(int m=-model;m<=model;m++)
				{
					int t=i*iDimX*iDimY+(j+m)*iDimX+k;
					count+=pVal[t];
				}
				pValTemp[i*iDimX*iDimY+j*iDimX+k]=count;
			}
		}
	}
	//z方向
	for(int i=model;i<iDimZ-model;i++)
	{
		for(int j=model;j<iDimY-model;j++)
		{
			for(int k=model;k<iDimX-model;k++)
			{
				int count=0;
				for(int m=-model;m<=model;m++)
				{
					int t=(i+m)*iDimX*iDimY+j*iDimX+k;
					count+=pValTemp[t];
				}
				if(count>thre)pMask_temp[i*iDimX*iDimY+j*iDimX+k]=LIVER_8SEGMENT_WHOLE;
				else pMask_temp[i*iDimX*iDimY+j*iDimX+k]=OTHERS;
			}
		}
	}
	delete[] pValTemp;
	delete[] pVal;

}

//在整个肝脏区域运用距离变换图，分水岭方法分割肝尾叶
//void SegFunction::seg_CaudateLobe(char *pAllMask,const int *iDim) //分割尾叶
//{
//	int len=iDim[0]*iDim[1]*iDim[2];
//	int pageSize=iDim[0]*iDim[1];
//	int *dis=new int[len];
//	memset(dis,0,len*sizeof(int));
//
//	time_t timeBeg,timeEnd1;
//	timeBeg=time(NULL);
//
//	DisGraph(pAllMask,dis,iDim);
//	int min=dis[0];
//	int max=dis[0];
//	for(int i=1;i<len;i++)
//	{
//	  if(dis[i]<min) min=dis[i];
//	  if(dis[i]>max) max=dis[i];
//	}
//	float *greyData=new float[len]; //灰度图
//	float *result=new float[len];
//	for(int i=0;i<len;i++)
//	{
//	   greyData[i]=dis[i]*255/(max-min);
//	}
//	//writeData(greyData,"F:\\CentreLine2\\HIU16\\06_LingMengMeng\\greyGraph_18.raw",iDim);
//	//针对灰度图进行高斯平滑
//	 int Ng;
//	 Ng=static_cast<int>(ceil(fNgParm*std_Gb))+1;
//	 std_Gb=5*fStdGbParm/fNorm;
//	 Gaussian_3D(result,Ng,std_Gb,greyData);
//	 //writeData(result,"F:\\CentreLine2\\HIU16\\06_LingMengMeng\\pinghua_18_5.raw",iDim);
//	 //寻找距离肝静脉分叉点和门脉分叉点连线最近的极大值点
//	 int tempPos=0;
//	 int searchResult[3];
//	 int mindisPoint[3]; //保存 距离肝静脉分叉点和门脉分叉点连线最近的极大值点
//	 double distance;
//	 int flag=0;
//	 //std::queue<Point3D<int>>Q;
//	 //vector<double> tempDistace;
//	 unsigned char * SeedImage=new unsigned char[len];
//	 memset(SeedImage,0,sizeof(unsigned char)*len);
//	 int num=0;
//	 for(int i=0;i<iDim[2];i++)
//		 for(int j=0;j<iDim[1];j++)
//			 for(int k=0;k<iDim[0];k++)
//	           {
//	             if((result[tempPos]>0) && maxPoint(result,k,j,i,iDim)) 
//				 {
//                   searchResult[0]=k;
//				   searchResult[1]=j;
//				   searchResult[2]=i;
//				   double tempdis=pointToPoint(searchResult,portalPoint);
//				   num++;
//				   SeedImage[tempPos]=num;
//				   //Q.push(Point3D<int>(searchResult[0],searchResult[1],searchResult[2]));
//				   //tempDistace.push_back(tempdis);
//				   //double tempdis=pointToLine(searchResult,veinPoint,portalPoint);
//				   
//				   if(flag==0) 
//				   {
//					   distance=tempdis;
//					   mindisPoint[0]=searchResult[0];
//					   mindisPoint[1]=searchResult[1];
//					   mindisPoint[2]=searchResult[2];
//					   flag=1;
//				   }
//				   else 
//				   {
//				     if(tempdis<distance)
//					 {
//					   distance=tempdis;  //更新距离，更新保存的极值点
//					   mindisPoint[0]=searchResult[0];
//					   mindisPoint[1]=searchResult[1];
//					   mindisPoint[2]=searchResult[2];
//					 }
//				   }
//				 }
//				 tempPos++;
//	           }
//	// int tempDistacePos=0;
//	// int maxGrey=0;
// //    while(!Q.empty())
//	//{
//	//	Point3D<int> &cur=Q.front();
//	//	if(tempDistace[tempDistacePos]-distance<5 && result[cur.z*pageSize+cur.y*iDim[0]+cur.x]>maxGrey) //设置到最小距离的范围为5
//	//	{
//	//	  maxGrey=result[cur.z*pageSize+cur.y*iDim[0]+cur.x];
//	//	  mindisPoint[0]=cur.x;
//	//	  mindisPoint[1]=cur.y;
//	//      mindisPoint[2]=cur.z;
//	//	}
//	//	Q.pop();
//	//}
//    unsigned char *pSrc=new unsigned char[len];
//	char *pDst=new char[len];
//	for(int i=0;i<len;i++)
//	{
//	  if(result[i]>255) pSrc[i]=255;
//	  else
//		  pSrc[i]=static_cast<unsigned char>(int(result[i]));
//	}
//	//pSrc归一化到0-255 代价图   SeedImage 种子点 标签从1开始
//    WaterShedNew(pSrc,SeedImage,pDst,iDim,pAllMask,num);
//	int seed=mindisPoint[2]*pageSize+mindisPoint[1]*iDim[0]+mindisPoint[0];
//	  //int color=pDst[seed];
//	for(int i=0;i<len;i++)
//	{
//	  if(pDst[i]==pDst[seed])
//		  pAllMask[i]=LIVER_8SEGMENT_PART9;
//	}
//	delete[]pSrc;
//	delete[]pDst;
//	delete[]SeedImage;
//    //GrowOnPoint(result,pAllMask,mindisPoint,iDim);
//	writeData(pAllMask,"F:\\CentreLine2\\HIU16\\06_LingMengMeng\\gaiweiye_watershed.raw",iDim);
// //   //显示找到的所有极值点以及血管连线
//	//char *pointMask=new char[len];
//	//memset(pointMask,0,len*sizeof(char));
//	//int color=1;
//	//while(!Q.empty())
//	//{
//	//	Point3D<int> &cur=Q.front();
//	//	for(int i=cur.z-1;i<=cur.z+1;i++)
//	//		for(int j=cur.y-1;j<=cur.y+1;j++)
//	//			for(int k=cur.x-1;k<=cur.x+1;k++)
//	//			{
//	//			   pointMask[i*pageSize+j*iDim[0]+k]=color;
//	//			}
//	//			Q.pop();
//	//			color++;
//	//}
//	///*std::queue<Point3D<int>>Q1;
//	//int vector[3];
//	//vector[0]=veinPoint[0]-portalPoint[0];
//	//vector[1]=veinPoint[1]-portalPoint[1];
//	//vector[2]=veinPoint[2]-portalPoint[2];
//	//Q1.push(Point3D<int>(veinPoint[0],veinPoint[1],veinPoint[2]));
//	//Q1.push(Point3D<int>(portalPoint[0],portalPoint[1],portalPoint[2]));
//	//for(int i=0;i<iDim[2];i++)
//	//	 for(int j=0;j<iDim[1];j++)
//	//		 for(int k=0;k<iDim[0];k++)
//	//		 {
//	//		   int ratio_x=(k-veinPoint[0])/vector[0];
//	//		   int ratio_y=(j-veinPoint[1])/vector[1];
//	//		   int ratio_z=(i-veinPoint[2])/vector[2];
//	//		   if(ratio_x==ratio_y && ratio_x==ratio_z) 
//	//		   {
//	//			   Q1.push(Point3D<int>(k,j,i));
//	//			   int pointpos=i*pageSize+j*iDim[0]+k;
//	//				if(pointpos>0 && pointpos<len)
//	//			      pointMask[i*pageSize+j*iDim[0]+k]=color;
//	//		   }
//	//		 }*/  //显示血管连线
// ////    while(!Q1.empty())
//	////{
//	////	Point3D<int> &cur=Q1.front();
//	////	for(int i=cur.z-1;i<=cur.z+1;i++)
//	////		for(int j=cur.y-1;j<=cur.y+1;j++)
//	////			for(int k=cur.x-1;k<=cur.x+1;k++)
//	////			{
//	////				int pointpos=i*pageSize+j*iDim[0]+k;
//	////				if(pointpos>0 && pointpos<len)
//	////			      pointMask[i*pageSize+j*iDim[0]+k]=color;
//	////			}
//	////			Q1.pop();
//	////			//color++;
//	////}
//	//writeData(pointMask,"F:\\CentreLine2\\HIU16\\06_LingMengMeng\\color_18_5.raw",iDim);
// //   delete[]pointMask;
//
//    timeEnd1=time(NULL);
//	int timeCost=timeEnd1-timeBeg;   
//	delete[]dis;
//	delete[]greyData;
//	delete[]result;
//}

/*
 * 平移变换函数 translateTran
 * 参数：
 *      iTranOriginal 变换后的坐标原点
 *		iTranDim      变换后的图像xyz
 *		pMask         原图像的mask
 *		iDim		  原图像的xyz
 *
 * 返回值： 变换后图像的mask
 *
 *
 */
char* SegFunction::translateTran(int* iTranOriginal, int *iTranDim, char *pMask8, const int *iDim)
{
	if(nullptr == pMask8 || nullptr == iDim || nullptr == iTranOriginal || nullptr == iTranDim)
		return NULL;

	int iLength = iDim[0] * iDim[1] * iDim[2]; // 原始图像的大小
	int iSizeXY = iDim[0] * iDim[1];           // 原始图像的页面大小(一层)
	int iMinX, iMaxX;
	int iMinY, iMaxY;
	int iMinZ, iMaxZ;
	bool firstIn = true;
	// 求出2，3段中最大最小边界
	for(int i = 0; i < iLength; i++)
	{
		if(LIVER_8SEGMENT_PART2 == pMask8[i] || LIVER_8SEGMENT_PART3 == pMask8[i]) // 图像中2、3段以外的mask值均为0
		{
			// 求出肝在原始图像中的坐标
			int zz = i / iSizeXY;            
			int yy = i % iSizeXY / iDim[0];
			int xx = i % iDim[0];

			if(firstIn)
			{
				iMinX = iMaxX = xx;   // 赋初值
				iMinY = iMaxY = yy;
				iMinZ = iMaxZ = zz;
				firstIn = false;
			}

			if(xx < iMinX) 
				iMinX = xx;
			else if(xx > iMaxX)
				iMaxX = xx;

			if(yy < iMinY) 
				iMinY = yy;
			else if(yy > iMaxY)
				iMaxY = yy;

			if(zz < iMinZ) 
				iMinZ = zz;
			else if(zz > iMaxZ)
				iMaxZ = zz;
		}
	}

	// 若变换后图像的原点不在xyz轴的边界上，原点和长宽高分别减1和加1 （在图像周围多长一圈）
	// 求出变换后图像的原点和长宽高xyz
	if(iMinX == 0 || iMinY == 0 || iMinZ == 0)
	{
		// 求出变换后图像原点
		iTranOriginal[0] = iMinX;
		iTranOriginal[1] = iMinY;
		iTranOriginal[2] = iMinZ;

		// 求出变换后图像的长宽高
		iTranDim[0] = iMaxX - iMinX + 1; 
		iTranDim[1] = iMaxY - iMinY + 1;
		iTranDim[2] = iMaxZ - iMinZ + 1;
	}
	else
	{
		iTranOriginal[0] = iMinX - 1;
		iTranOriginal[1] = iMinY - 1;
		iTranOriginal[2] = iMinZ - 1;

		iTranDim[0] = (iMaxX - iMinX + 1) + 2; 
		iTranDim[1] = (iMaxY - iMinY + 1) + 2;
		iTranDim[2] = (iMaxZ - iMinZ + 1) + 2;
	}
	
	int iTranLength = iTranDim[0] * iTranDim[1] * iTranDim[2];    // 平移变换后图像的大小
	int iTranSizeXY = iTranDim[0] * iTranDim[1];                  // 平移变换后图像的页面大小(一层)

	// 存储平移变换之后的mask和raw
	char *pTranMask = new char[iTranLength];
	short *pTranRaw = new short[iTranLength];

	for(int i = 0; i < iTranLength; i++)
	{
		// 求变换后图像位置的坐标
		int zz = i / iTranSizeXY;
		int yy = i % iTranSizeXY / iTranDim[0];
		int xx = i % iTranDim[0];

		int positionI = (zz + iTranOriginal[2]) * iSizeXY + (yy + iTranOriginal[1]) * iDim[0] + (xx + iTranOriginal[0]); // 算出标签映射回原图像的坐标位置
		if(LIVER_8SEGMENT_PART2 == pMask8[positionI] || LIVER_8SEGMENT_PART3 == pMask8[positionI])
		{
			pTranMask[i] = pMask8[positionI];      		
		}
		else
		{
			pTranMask[i] = 0;
		}
	}

	writeData(pTranRaw, gFileName + "tranRaw.raw", iTranDim);   //输出变换后的Raw
	writeData(pTranMask, gFileName + "tranMask.raw", iTranDim); //输出变换后的Mask
	ofstream tranParam(gFileName + "tranParam.txt");
    if (tranParam.is_open())
    {
        tranParam << "iTranOriginal" << endl;
		tranParam << "xOriginal = " << iTranOriginal[0] << "\nyOriginal = " << iTranOriginal[1] << "\nzOriginal = " << iTranOriginal[2] << endl;
		tranParam << "\niTranDim\n";
		tranParam << "x = " << iTranDim[0] << "\ny = " << iTranDim[1] << "\nz = " << iTranDim[2] << "\n";
		tranParam << "Z_iStart = " << iStart << "\nZ_iEnd = " << iEnd;
        tranParam.close();
    }
	return pTranMask;
}

/*
 * 平移变换函数 translateTran  并输出中间结果Raw
 * 参数：
 *      iTranOriginal 变换后的坐标原点
 *		iTranDim      变换后的图像xyz
 *      pData_Base    原始灰度图像数据
 *		pMask         原图像的mask
 *		iDim		  原图像的xyz
 *
 * 返回值： 变换后图像的mask
 *
 *
 */
char* SegFunction::translateTran(int *iTranOriginal, int *iTranDim, short *pData_Base, char *pMask8, const int *iDim)
{
	if(nullptr == pMask8 || nullptr == iDim || nullptr == iTranOriginal || nullptr == iTranDim || nullptr == pData_Base)
		return NULL;

	int iLength = iDim[0] * iDim[1] * iDim[2]; // 原始图像的大小
	int iSizeXY = iDim[0] * iDim[1];           // 原始图像的页面大小(一层)
	int iMinX, iMaxX;
	int iMinY, iMaxY;
	int iMinZ, iMaxZ;
	bool firstIn = true;
	// 求出2，3段中最大最小边界
	for(int i = 0; i < iLength; i++)
	{
		if(LIVER_8SEGMENT_PART2 == pMask8[i] || LIVER_8SEGMENT_PART3 == pMask8[i]) // 图像中2、3段以外的mask值均为0
		{
			// 求出肝在原始图像中的坐标
			int zz = i / iSizeXY;            
			int yy = i % iSizeXY / iDim[0];
			int xx = i % iDim[0];

			if(firstIn)
			{
				iMinX = iMaxX = xx;   // 赋初值
				iMinY = iMaxY = yy;
				iMinZ = iMaxZ = zz;
				firstIn = false;
			}

			if(xx < iMinX) 
				iMinX = xx;
			else if(xx > iMaxX)
				iMaxX = xx;

			if(yy < iMinY) 
				iMinY = yy;
			else if(yy > iMaxY)
				iMaxY = yy;

			if(zz < iMinZ) 
				iMinZ = zz;
			else if(zz > iMaxZ)
				iMaxZ = zz;
		}
	}

	// 若变换后图像的原点不在xyz轴的边界上，原点和长宽高分别减1和加1 （在图像周围多长一圈）
	// 求出变换后图像的原点和长宽高xyz
	if(iMinX == 0 || iMinY == 0 || iMinZ == 0)
	{
		// 求出变换后图像原点
		iTranOriginal[0] = iMinX;
		iTranOriginal[1] = iMinY;
		iTranOriginal[2] = iMinZ;

		// 求出变换后图像的长宽高
		iTranDim[0] = iMaxX - iMinX + 1; 
		iTranDim[1] = iMaxY - iMinY + 1;
		iTranDim[2] = iMaxZ - iMinZ + 1;
	}
	else
	{
		iTranOriginal[0] = iMinX - 1;
		iTranOriginal[1] = iMinY - 1;
		iTranOriginal[2] = iMinZ - 1;

		iTranDim[0] = (iMaxX - iMinX + 1) + 2; 
		iTranDim[1] = (iMaxY - iMinY + 1) + 2;
		iTranDim[2] = (iMaxZ - iMinZ + 1) + 2;
	}
	
	int iTranLength = iTranDim[0] * iTranDim[1] * iTranDim[2];    // 平移变换后图像的大小
	int iTranSizeXY = iTranDim[0] * iTranDim[1];                  // 平移变换后图像的页面大小(一层)

	// 存储平移变换之后的mask和raw
	char *pTranMask = new char[iTranLength];
	short *pTranRaw = new short[iTranLength];

	for(int i = 0; i < iTranLength; i++)
	{
		// 求变换后图像位置的坐标
		int zz = i / iTranSizeXY;
		int yy = i % iTranSizeXY / iTranDim[0];
		int xx = i % iTranDim[0];

		int positionI = (zz + iTranOriginal[2]) * iSizeXY + (yy + iTranOriginal[1]) * iDim[0] + (xx + iTranOriginal[0]); // 算出标签映射回原图像的坐标位置
		if(LIVER_8SEGMENT_PART2 == pMask8[positionI] || LIVER_8SEGMENT_PART3 == pMask8[positionI])
		{
			pTranMask[i] = pMask8[positionI];      		
		}
		else
		{
			pTranMask[i] = 0;
		}
		/* 算出CT映射回原图像的坐标位置
		 * 由于在分割八段时，已经算出了肝脏位置Z轴方向的最大iEnd和最小iStart（全局变量）
		 * 所以映射CT时需要算上已经被截小的CT图像的坐标
		 */
		int positionCT = (zz + iTranOriginal[2] - iStart) * iSizeXY + (yy + iTranOriginal[1]) * iDim[0] + (xx + iTranOriginal[0]); 
		pTranRaw[i] = pData_Base[positionCT];
	}

	writeData(pTranRaw, gFileName + "tranRaw.raw", iTranDim);   //输出变换后的Raw
	writeData(pTranMask, gFileName + "tranMask.raw", iTranDim); //输出变换后的Mask
	ofstream tranParam(gFileName + "tranParam.txt");
    if (tranParam.is_open())
    {
        tranParam << "iTranOriginal" << endl;
		tranParam << "xOriginal = " << iTranOriginal[0] << "\nyOriginal = " << iTranOriginal[1] << "\nzOriginal = " << iTranOriginal[2] << endl;
		tranParam << "\niTranDim\n";
		tranParam << "x = " << iTranDim[0] << "\ny = " << iTranDim[1] << "\nz = " << iTranDim[2] << "\n";
		tranParam << "Z_iStart = " << iStart << "\nZ_iEnd = " << iEnd;
        tranParam.close();
    }
	return pTranMask;
}

void SegFunction::calculateTranDim(int* iTranOriginal, int *iTranDim, char *pMask8, const int *iDim)
{
	if(nullptr == iTranOriginal || nullptr == iTranDim || nullptr == pMask8 || nullptr == iDim)
		return ;

	int iLength = iDim[0] * iDim[1] * iDim[2]; // 原始图像的大小
	int iSizeXY = iDim[0] * iDim[1];           // 原始图像的页面大小(一层)
	int iMinX, iMaxX;
	int iMinY, iMaxY;
	int iMinZ, iMaxZ;
	bool firstIn = true;
	// 求出2，3段中最大最小边界
	for(int i = 0; i < iLength; i++)
	{
		if(LIVER_8SEGMENT_PART2 == pMask8[i] || LIVER_8SEGMENT_PART3 == pMask8[i]) // 图像中2、3段以外的mask值均为0
		{
			// 求出肝在原始图像中的坐标
			int zz = i / iSizeXY;            
			int yy = i % iSizeXY / iDim[0];
			int xx = i % iDim[0];

			if(firstIn)
			{
				iMinX = iMaxX = xx;   // 赋初值
				iMinY = iMaxY = yy;
				iMinZ = iMaxZ = zz;
				firstIn = false;
			}

			if(xx < iMinX) 
				iMinX = xx;
			else if(xx > iMaxX)
				iMaxX = xx;

			if(yy < iMinY) 
				iMinY = yy;
			else if(yy > iMaxY)
				iMaxY = yy;

			if(zz < iMinZ) 
				iMinZ = zz;
			else if(zz > iMaxZ)
				iMaxZ = zz;
		}
	}

	// 若变换后图像的原点不在xyz轴的边界上，原点和长宽高分别减1和加1 （在图像周围多长一圈）
	// 求出变换后图像的原点和长宽高xyz
	if(iMinX == 0 || iMinY == 0 || iMinZ == 0)
	{
		// 求出变换后图像原点
		iTranOriginal[0] = iMinX;
		iTranOriginal[1] = iMinY;
		iTranOriginal[2] = iMinZ;

		// 求出变换后图像的长宽高
		iTranDim[0] = iMaxX - iMinX + 1; 
		iTranDim[1] = iMaxY - iMinY + 1;
		iTranDim[2] = iMaxZ - iMinZ + 1;
	}
	else
	{
		iTranOriginal[0] = iMinX - 1;
		iTranOriginal[1] = iMinY - 1;
		iTranOriginal[2] = iMinZ - 1;

		iTranDim[0] = (iMaxX - iMinX + 1) + 2; 
		iTranDim[1] = (iMaxY - iMinY + 1) + 2;
		iTranDim[2] = (iMaxZ - iMinZ + 1) + 2;
	}
}

void SegFunction::translateTran(int *iTranOriginal, int *iTranDim, short *pTranRaw, char *pTranMask, short *pData_Base, char *pMask8, const int *iDim)
{
	if(nullptr == iTranOriginal || nullptr == iTranDim || nullptr == pTranMask || nullptr == pTranRaw || nullptr == pData_Base || nullptr == pMask8 || nullptr == iDim)
		return ;

	//int iLength = iDim[0] * iDim[1] * iDim[2]; // 原始图像的大小
	int iSizeXY = iDim[0] * iDim[1];           // 原始图像的页面大小(一层)

	int iTranLength = iTranDim[0] * iTranDim[1] * iTranDim[2];    // 平移变换后图像的大小
	int iTranSizeXY = iTranDim[0] * iTranDim[1];                  // 平移变换后图像的页面大小(一层)

	for(int i = 0; i < iTranLength; i++)
	{
		// 求变换后图像位置的坐标
		int zz = i / iTranSizeXY;
		int yy = i % iTranSizeXY / iTranDim[0];
		int xx = i % iTranDim[0];

		int positionI = (zz + iTranOriginal[2]) * iSizeXY + (yy + iTranOriginal[1]) * iDim[0] + (xx + iTranOriginal[0]); // 算出标签映射回原图像的坐标位置
		if(LIVER_8SEGMENT_PART2 == pMask8[positionI] || LIVER_8SEGMENT_PART3 == pMask8[positionI])
		{
			pTranMask[i] = pMask8[positionI];      		
		}
		else
		{
			pTranMask[i] = 0;
		}
		/* 算出CT映射回原图像的坐标位置
		 * 由于在分割八段时，已经算出了肝脏位置Z轴方向的最大iEnd和最小iStart（全局变量）
		 * 所以映射CT时需要算上已经被截小的CT图像的坐标
		 */
		int positionCT = (zz + iTranOriginal[2] - iStart) * iSizeXY + (yy + iTranOriginal[1]) * iDim[0] + (xx + iTranOriginal[0]); 
		pTranRaw[i] = pData_Base[positionCT];
	}

	writeData(pTranRaw, gFileName + "tranRaw.raw", iTranDim);   //输出变换后的Raw
	writeData(pTranMask, gFileName + "tranMask.raw", iTranDim); //输出变换后的Mask
	ofstream tranParam(gFileName + "tranParam.txt");
    if (tranParam.is_open())
    {
        tranParam << "iTranOriginal" << endl;
		tranParam << "xOriginal = " << iTranOriginal[0] << "\nyOriginal = " << iTranOriginal[1] << "\nzOriginal = " << iTranOriginal[2] << endl;
		tranParam << "\niTranDim\n";
		tranParam << "x = " << iTranDim[0] << "\ny = " << iTranDim[1] << "\nz = " << iTranDim[2] << "\n";
		tranParam << "Z_iStart = " << iStart << "\nZ_iEnd = " << iEnd;
        tranParam.close();
    }
}

/*
 * 平移逆变换函数 translateTranReverse
 * 参数：
 *      iTranOriginal 变换后的坐标原点
 *		iTranDim      变换后的图像xyz
 *		pTranMask     变换后图像的mask
 *		pMask8        用于恢复原始图像分割的肝八段
 *		iDim		  原图像的xyz
 *
 * 返回值： 逆变换（还原）后图像的mask
 *
 *
 */
char* SegFunction::translateTranReverse(int *iTranOriginal, const int *iTranDim, char *pTranMask, char *pMask8, const int *iDim)
{
	if(nullptr == pTranMask || nullptr == iDim || nullptr == iTranOriginal || nullptr == iTranDim || nullptr == pMask8)
		return NULL;

	int iLength = iDim[0] * iDim[1] * iDim[2]; // 原始图像的大小
	int iSizeXY = iDim[0] * iDim[1];           // 原始图像的页面大小(一层)

	int iTranLength = iTranDim[0] * iTranDim[1] * iTranDim[2];    // 平移变换后图像的大小
	int iTranSizeXY = iTranDim[0] * iTranDim[1];                  // 平移变换后图像的页面大小(一层)

	// 平移逆变换之后的mask和raw
	char *pMask = new char[iLength];
	short *pRaw = new short[iLength];

	for(int i = 0; i < iLength; i++)
	{
		pMask[i] = pMask8[i];	
	}

	for(int i = 0; i < iTranLength; i++)
	{
		int zz = i / iTranSizeXY;
		int yy = i % iTranSizeXY / iTranDim[0];
		int xx = i % iTranDim[0];
		int positionI = (zz + iTranOriginal[2]) * iSizeXY + (yy + iTranOriginal[1]) * iDim[0] + (xx + iTranOriginal[0]); // 算出映射回原图像的坐标位置
		if(LIVER_8SEGMENT_PART9 == pTranMask[i] || LIVER_8SEGMENT_PART7 == pTranMask[i])
		{
			pMask[positionI] = pTranMask[i];	
		}
	}
	return pMask;
}
// 只在2,3区域运用距离变换图，分水岭方法分割肝尾叶
void SegFunction::seg_CaudateLobe(char *pMask_2_3, const int *iDim) //分割尾叶
{
	int len = iDim[0] * iDim[1] * iDim[2];
	int pageSize = iDim[0] * iDim[1];
	int *dis = new int[len];
	memset(dis, 0, len * sizeof(int)); // dis内容全部置0
	
	 //计算并输出距离图
	DisGraph(pMask_2_3, dis, iDim);
	//writeData(dis, gFileName + "tranDisGraph.raw",iDim);

	int min = dis[0];
	int max = dis[0];
	for(int i = 1; i < len; i++)
	{
	  if(dis[i] < min) 
		  min = dis[i];
	  else if(dis[i] > max) 
		  max = dis[i];
	}
	float *greyData = new float[len]; //灰度图
	float *result = new float[len];
	for(int i = 0; i < len; i++)
	{
	   greyData[i] = dis[i] * 255 / (max - min);
	   //result[i]=greyData[i];
	}
	//writeData(greyData, gFileName + "greyData.raw", iDim);


	//针对灰度图进行高斯平滑
	 int Ng = 3;//static_cast<int>(ceil(fNgParm*std_Gb))+1; //fNgParm 6   std_Gb 1
	 std_Gb = 1 * fStdGbParm / fNorm; //fStdGbParm 3  fNorm 3
	 Gaussian_3D(result, Ng, std_Gb, greyData, iDim);
	 //writeData(result, gFileName + "pingHua.raw",iDim);
	 

	 //寻找距离肝静脉分叉点和门脉分叉点连线最近的极大值点
	 int tempPos=0;
	 int searchResult[3];
	 int mindisPoint[3]; //保存 距离肝静脉分叉点和门脉分叉点连线最近的极大值点
	 double distance;
	 int flag=0;
	 std::queue<Point3D<int>> Q;
	 vector<double> tempDistace;
	 unsigned char * SeedImage=new unsigned char[len];
	 memset(SeedImage,0,sizeof(unsigned char)*len);
	 int num=0;

	 vector<int> seedpoints;

	 for(int i=0;i<iDim[2];i++)
		 for(int j=0;j<iDim[1];j++)
			 for(int k=0;k<iDim[0];k++)
	           {
	             if((result[tempPos]>0) && maxPoint(result,k,j,i,iDim)) 
				 {
                   searchResult[0]=k;
				   searchResult[1]=j;
				   searchResult[2]=i;
				   double tempdis=pointToLine(searchResult,veinPoint,portalPoint);
				   if(tempdis<35)
					   seedpoints.push_back(tempPos);
				   num++;
				   SeedImage[tempPos]=num;
				   Q.push(Point3D<int>(searchResult[0],searchResult[1],searchResult[2]));
				   tempDistace.push_back(tempdis);
				 }
				 tempPos++;
	           }

    unsigned char *pSrc=new unsigned char[len];
	char *pDst=new char[len];
	for(int i=0;i<len;i++)
	{
	  if(result[i]>255) pSrc[i]=255;
	  else
		  pSrc[i]=static_cast<unsigned char>(int(result[i]));

	  //if(result[i]>0) SeedImage[i]=1;
	}
	//pSrc归一化到0-255 代价图   SeedImage 种子点 标签从1开始
	WaterShedNew(dis, SeedImage, pDst, iDim, pMask_2_3, num); //将平滑后的距离图换成之前的距离图
	//writeData(pDst, gFileName + "pDst.raw",iDim);
	for(int i=0;i<len;i++)
	{
		for(int j=0;j<seedpoints.size();j++)
		{
		  if(pDst[i]==pDst[seedpoints[j]])
		    pMask_2_3[i]=LIVER_8SEGMENT_PART9;
		}
	}
	//writeData(pMask_2_3, gFileName + "123.raw",iDim);
	delete[]pSrc;
	delete[]pDst;
	delete[]SeedImage;
	delete[]dis;
	delete[]greyData;
	delete[]result;
}

// 只在2,3区域运用距离变换图，分水岭方法分割肝尾叶
void SegFunction::seg_CaudateLobe(char *pMask_2_3, int *iTranOriginal, const int *iDim)//分割尾叶
{
	int len = iDim[0] * iDim[1] * iDim[2];
	int pageSize = iDim[0] * iDim[1];
	int *dis = new int[len];
	memset(dis, 0, len * sizeof(int)); // dis内容全部置0
	
	 // 计算并输出距离图
	DisGraph(pMask_2_3, dis, iDim);
	//writeData(dis,gFileName + "tranDisGraph.raw",iDim);

	// 求出最大最小距离
	int min = dis[0];
	int max = dis[0];
	for(int i = 1; i < len; i++)
	{
	  if(dis[i] < min) 
		  min = dis[i];
	  else if(dis[i] > max) 
		  max = dis[i];
	}

	// 计算灰度图
	float *greyData = new float[len];
	for(int i = 0; i < len; i++)
	{
	   greyData[i] = dis[i] * 255 / (max - min);
	   //result[i]=greyData[i];
	}
	//writeData(greyData, gFileName + "greyData.raw", iDim);


	//针对灰度图进行高斯平滑
	 float *result = new float[len];
	 int Ng = 3;//static_cast<int>(ceil(fNgParm*std_Gb))+1; //fNgParm 6   std_Gb 1
	 std_Gb = 1 * fStdGbParm / fNorm; //fStdGbParm 3  fNorm 3
	 Gaussian_3D(result, Ng, std_Gb, greyData, iDim);
	 //writeData(result,"E:\\ChenCongmei\\pingHua.raw",iDim);
	 

	 //寻找距离肝静脉分叉点和门脉分叉点连线最近的极大值点
	 int tempPos=0;
	 int searchResult[3];
	 int mindisPoint[3]; //保存 距离肝静脉分叉点和门脉分叉点连线最近的极大值点
	 double distance;
	 int flag=0;
	 std::queue<Point3D<int>> Q;
	 vector<double> tempDistace;
	 unsigned char * SeedImage=new unsigned char[len];
	 memset(SeedImage,0,sizeof(unsigned char)*len);
	 int num=0;

	 vector<int> seedpoints;

	 for(int i=0;i<iDim[2];i++)
		 for(int j=0;j<iDim[1];j++)
			 for(int k=0;k<iDim[0];k++)
	           {
	             if((result[tempPos]>0) && maxPoint(result,k,j,i,iDim)) 
				 {
                   searchResult[0]=k;
				   searchResult[1]=j;
				   searchResult[2]=i;
				   double tempdis = pointToLine(searchResult,veinPoint,portalPoint, iTranOriginal); // veinPoint（下腔静脉血管点） portalPoint（门脉血管点）在原始图像中手工选取
				   if(tempdis<35)
					   seedpoints.push_back(tempPos);
				   num++;
				   SeedImage[tempPos]=num;
				   Q.push(Point3D<int>(searchResult[0],searchResult[1],searchResult[2]));
				   tempDistace.push_back(tempdis);
				 }
				 tempPos++;
	           }

    unsigned char *pSrc=new unsigned char[len];
	char *pDst=new char[len];
	for(int i=0;i<len;i++)
	{
	  if(result[i]>255) pSrc[i]=255;
	  else
		  pSrc[i]=static_cast<unsigned char>(int(result[i]));

	  //if(result[i]>0) SeedImage[i]=1;
	}
	//pSrc归一化到0-255 代价图   SeedImage 种子点 标签从1开始
	WaterShedNew(dis, SeedImage, pDst, iDim, pMask_2_3, num); //将平滑后的距离图换成之前的距离图
	writeData(pDst, gFileName + "pDst.raw",iDim);

	// 给尾叶赋标签
	for(int i=0;i<len;i++)
	{
		for(int j=0;j<seedpoints.size();j++)
		{
		  if(pDst[i]==pDst[seedpoints[j]])
		    pMask_2_3[i]=LIVER_8SEGMENT_PART9;
		}
	}
	
	//writeData(pMask_2_3, gFileName + "watershed_3_1.raw", iDim);

	delete[]pSrc;
	delete[]pDst;
	delete[]SeedImage;
	delete[]dis;
	delete[]greyData;
	delete[]result;
}


void SegFunction::seg_CaudateLobe_manual_cut(char *pMask_2_3, int *iTranOriginal, const int *iDim)
{
	int len = iDim[0] * iDim[1] * iDim[2];
	int pageSize = iDim[0] * iDim[1];
	int *dis = new int[len];
	memset(dis, 0, len * sizeof(int)); // dis内容全部置0


	// ChenKaiyu
	/*int pointa[3]={218,204,524};  
	int pointb[3]={216,227,524};*/
	
	// WangChaofeng
	/*int pointa[3]={260,249,284};  
	int pointb[3]={260,221,235};*/
	
	// HuangGuanglan
	/*int pointa[3]={223,219,474};  
	int pointb[3]={272,233,474};*/

	// ChenCongmei
	int pointa[3] = {230,238,43};  
	int pointb[3] = {245,241,43}; 

	// ChenAnping
	/*int pointa[3]={209,215,494};  
	int pointb[3]={216,237,494}; */

	int z_position = pointa[2] - iTranOriginal[2]; //切割的那一层平移变换后的坐标
	int tempPoint[3]={0,0,0};
	for(int i=0;i<len;i++)
	{
		  tempPoint[2] = i / pageSize;                //z
		  tempPoint[1] = i % pageSize / iDim[0];      //y
		  tempPoint[0] = i % iDim[0];                //x
		  if(pointToLine(tempPoint,pointa,pointb, iTranOriginal)<3) 
			  pMask_2_3[i]=0;
	}

	 // 计算并输出距离图
	DisGraph(pMask_2_3, dis, iDim);
	writeData(dis,gFileName + "tranDisGraphManual.raw",iDim);

	// 求出最大最小距离
	int min = dis[0];
	int max = dis[0];
	for(int i = 1; i < len; i++)
	{
	  if(dis[i] < min) 
		  min = dis[i];
	  else if(dis[i] > max) 
		  max = dis[i];
	}

	// 计算灰度图
	float *greyData = new float[len];
	for(int i = 0; i < len; i++)
	{
	   greyData[i] = dis[i] * 255 / (max - min);
	   //result[i]=greyData[i];
	}
	//writeData(greyData, gFileName + "greyData.raw", iDim);


	//针对灰度图进行高斯平滑
	 float *result = new float[len];
	 int Ng = 3;//static_cast<int>(ceil(fNgParm*std_Gb))+1; //fNgParm 6   std_Gb 1
	 std_Gb = 1 * fStdGbParm / fNorm; //fStdGbParm 3  fNorm 3
	 Gaussian_3D(result, Ng, std_Gb, greyData, iDim);
	 //writeData(result, gFileName + "pingHua.raw",iDim);
	 

	 //寻找距离肝静脉分叉点和门脉分叉点连线最近的极大值点
	 int tempPos=0;
	 int searchResult[3];
	 int mindisPoint[3]; //保存 距离肝静脉分叉点和门脉分叉点连线最近的极大值点
	 double distance;
	 int flag=0;
	 std::queue<Point3D<int>> Q;
	 vector<double> tempDistace;
	 unsigned char * SeedImage=new unsigned char[len];
	 memset(SeedImage,0,sizeof(unsigned char)*len);
	 int num=0;

	 vector<int> seedpoints;

	 for(int i=0;i<iDim[2];i++)
		 for(int j=0;j<iDim[1];j++)
			 for(int k=0;k<iDim[0];k++)
	           {
	             if((result[tempPos]>0) && maxPoint(result,k,j,i,iDim)) 
				 {
                   searchResult[0]=k;
				   searchResult[1]=j;
				   searchResult[2]=i;
				   double tempdis = pointToLine(searchResult,veinPoint,portalPoint, iTranOriginal); // veinPoint（下腔静脉血管点） portalPoint（门脉血管点）在原始图像中手工选取
				   if(tempdis<32)
					   seedpoints.push_back(tempPos);
				   num++;
				   SeedImage[tempPos]=num;
				   Q.push(Point3D<int>(searchResult[0],searchResult[1],searchResult[2]));
				   tempDistace.push_back(tempdis);
				 }
				 tempPos++;
	           }

    unsigned char *pSrc=new unsigned char[len];
	char *pDst=new char[len];
	for(int i=0;i<len;i++)
	{
	  if(result[i]>255) pSrc[i]=255;
	  else
		  pSrc[i]=static_cast<unsigned char>(int(result[i]));

	  //if(result[i]>0) SeedImage[i]=1;
	}
	//pSrc归一化到0-255 代价图   SeedImage 种子点 标签从1开始
	WaterShedNew(dis, SeedImage, pDst, iDim, pMask_2_3, num); //将平滑后的距离图换成之前的距离图
	writeData(pDst, gFileName + "pDst.raw",iDim);

	//因为进行了切割，所以需要判断哪一块是切割掉的
	
	
	int pointAOnPlane[2];
	pointAOnPlane[0]=pointa[0]-iTranOriginal[0];
	pointAOnPlane[1]=pointa[1]-iTranOriginal[1];

	int pointBOnPlane[2];
	pointBOnPlane[0]=pointb[0]-iTranOriginal[0];
	pointBOnPlane[1]=pointb[1]-iTranOriginal[1];

	// 求中点
	/*int pointMiddleOnPlane[2];
	pointMiddleOnPlane[0] = (pointAOnPlane[0] + pointBOnPlane[0]) / 2;
	pointMiddleOnPlane[1] = (pointAOnPlane[1] + pointBOnPlane[1]) / 2;*/

	float line[2];
	generate_line_2point(pointAOnPlane,pointBOnPlane,line);
	
	//int pointTemp[2];
	//只观察z=z_position 这一层
	vector<int> label1(num,0);
	vector<int> label2(num,0);
	/*int count1=0;
	int count2=0;*/
	for(int i=0;i<iDim[0];i++) //x
		for(int j=0;j<iDim[1];j++) //y
		{
			int pos = z_position*pageSize+j*iDim[0]+i;

			//pointTemp[0] = i;
			//pointTemp[1] = j;
			//if(pointToPoint2D(pointTemp, pointMiddleOnPlane) > 45)
			//	continue;
			if(pDst[pos]) //pDst分水岭结果
			{
			  if(line[0]*i+line[1]>j)   // kx + b > y
			  {
			     //count1++;
				 label1[pDst[pos] - 1] += 1;
			  }
			  else 
			  {
			     //count2++;
				 label2[pDst[pos] - 1] += 1;
			  }
			}
		}

    int count1=0;
	int count2=0;
	int count3=0;
	int centrePoint1[3] = {0, 0, 0};
	int centrePoint2[3] = {0, 0, 0};
	int centrePoint3[3] = {0, 0, 0};
    for(int k=0;k<iDim[2];k++)
		for(int j=0;j<iDim[1];j++)
			for(int i=0;i<iDim[0];i++)
			{
				  int pos=k*pageSize+j*iDim[0]+i;
				  if(pos < len && pDst[pos])
				  {
					count3++;
					centrePoint3[0]+=i;
					centrePoint3[1]+=j;
					centrePoint3[2]+=k;
					if(pDst[pos] > 0 && pDst[pos] <= num)
					{
						if(label1[pDst[pos] - 1])
						{
						   count1++;
						   centrePoint1[0]+=i;
						   centrePoint1[1]+=j;
						   centrePoint1[2]+=k;
						}
						if(label2[pDst[pos] - 1])
						{
						   count2++;
						   centrePoint2[0]+=i;
						   centrePoint2[1]+=j;
						   centrePoint2[2]+=k;
						}
					}
				  }
			}

	char iFlagCount = 0;
	if(0 == count1)
		iFlagCount = 1;
	else
	{
		centrePoint1[0]/=count1;
		centrePoint1[1]/=count1;
		centrePoint1[2]/=count1;
	}
    
	if(0 == count2)
		iFlagCount = 2;
	else
	{
		centrePoint2[0]/=count2;
		centrePoint2[1]/=count2;
		centrePoint2[2]/=count2;
	}

	if(0 == count3)
		return ;
	
	centrePoint3[0]/=count3;
	centrePoint3[1]/=count3;
	centrePoint3[2]/=count3;


   //将需要割去的标签保存在label1中
   if(0 == iFlagCount && pointToPoint(centrePoint1,centrePoint3) < pointToPoint(centrePoint2,centrePoint3)) //count1 > count2
   {
		 for(int i = 0; i < num; i++)
		 {
			 if(0 == label1[i])
			 {
				label1[i] = label2[i];
			 }
			 else 
			 {
				label1[i] = 0;
			 }
		 }
   }
   else
   {
		for(int i = 0; i < num; i++)
		 {
			if(label2[i] > 0)
			{
				label1[i] = 0;
			}
		 }
   }

	// 给尾叶赋标签
	for(int i=0;i<len;i++)
	{
		for(int j=0;j<seedpoints.size();j++)
		{
		  if(pDst[i] == pDst[seedpoints[j]] && 0 == label1[pDst[i] - 1])
		    pMask_2_3[i]=LIVER_8SEGMENT_PART9;
		}
	}
	
	delete[]pSrc;
	delete[]pDst;
	delete[]SeedImage;

	//writeData(pMask_2_3, gFileName+"watershed_3_1.raw",iDim);

	delete[]dis;
	delete[]greyData;
	delete[]result;
  
}

void SegFunction::seg_CaudateLobe_manual_mend(char *pMask_2_3, int *iTranOriginal, const int *iDim)
{
	int len = iDim[0] * iDim[1] * iDim[2];
	int pageSize = iDim[0] * iDim[1];
	int *dis = new int[len];
	memset(dis, 0, len * sizeof(int)); // dis内容全部置0


	// ChenKaiyu
	/*int pointa[3]={218,204,524};  
	int pointb[3]={216,227,524};*/
	
	// WangChaofeng
	/*int pointa[3]={260,249,284};  
	int pointb[3]={260,221,235};*/
	
	// HuangGuanglan
	/*int pointa[3]={223,219,474};  
	int pointb[3]={272,233,474};*/

	// ChenCongmei
	int pointa[3] = {230,238,43};  
	int pointb[3] = {245,241,43}; 

	// ChenAnping
	/*int pointa[3]={209,215,494};  
	int pointb[3]={216,237,494};*/ 
	int z_position = pointa[2] - iTranOriginal[2]; //切割的那一层平移变换后的坐标
	int tempPoint[3]={0,0,0};
	for(int i=0;i<len;i++)
	{
		  tempPoint[2] = i / pageSize;                //z
		  tempPoint[1] = i % pageSize / iDim[0];      //y
		  tempPoint[0] = i % iDim[0];                //x
		  if(pointToLine(tempPoint,pointa,pointb, iTranOriginal)<3) 
			  pMask_2_3[i]=0;
	}

	 // 计算并输出距离图
	DisGraph(pMask_2_3, dis, iDim);
	writeData(dis,gFileName + "tranDisGraphManual.raw",iDim);

	// 求出最大最小距离
	int min = dis[0];
	int max = dis[0];
	for(int i = 1; i < len; i++)
	{
	  if(dis[i] < min) 
		  min = dis[i];
	  else if(dis[i] > max) 
		  max = dis[i];
	}

	// 计算灰度图
	float *greyData = new float[len];
	for(int i = 0; i < len; i++)
	{
	   greyData[i] = dis[i] * 255 / (max - min);
	   //result[i]=greyData[i];
	}
	//writeData(greyData, gFileName + "greyData.raw", iDim);


	//针对灰度图进行高斯平滑
	 float *result = new float[len];
	 int Ng = 3;//static_cast<int>(ceil(fNgParm*std_Gb))+1; //fNgParm 6   std_Gb 1
	 std_Gb = 1 * fStdGbParm / fNorm; //fStdGbParm 3  fNorm 3
	 Gaussian_3D(result, Ng, std_Gb, greyData, iDim);
	 //writeData(result, gFileName + "pingHua.raw",iDim);
	 

	 //寻找距离肝静脉分叉点和门脉分叉点连线最近的极大值点
	 int tempPos=0;
	 int searchResult[3];
	 int mindisPoint[3]; //保存 距离肝静脉分叉点和门脉分叉点连线最近的极大值点
	 double distance;
	 int flag=0;
	 std::queue<Point3D<int>> Q;
	 vector<double> tempDistace;
	 unsigned char * SeedImage=new unsigned char[len];
	 memset(SeedImage,0,sizeof(unsigned char)*len);
	 int num=0;

	 vector<int> seedpoints;

	 for(int i=0;i<iDim[2];i++)
		 for(int j=0;j<iDim[1];j++)
			 for(int k=0;k<iDim[0];k++)
	           {
	             if((result[tempPos]>0) && maxPoint(result,k,j,i,iDim)) 
				 {
                   searchResult[0]=k;
				   searchResult[1]=j;
				   searchResult[2]=i;
				   double tempdis = pointToLine(searchResult,veinPoint,portalPoint, iTranOriginal); // veinPoint（下腔静脉血管点） portalPoint（门脉血管点）在原始图像中手工选取
				   if(tempdis<32)
					   seedpoints.push_back(tempPos);
				   num++;
				   SeedImage[tempPos]=num;
				   Q.push(Point3D<int>(searchResult[0],searchResult[1],searchResult[2]));
				   tempDistace.push_back(tempdis);
				 }
				 tempPos++;
	           }

    unsigned char *pSrc=new unsigned char[len];
	char *pDst=new char[len];
	for(int i=0;i<len;i++)
	{
	  if(result[i]>255) pSrc[i]=255;
	  else
		  pSrc[i]=static_cast<unsigned char>(int(result[i]));

	  //if(result[i]>0) SeedImage[i]=1;
	}
	//pSrc归一化到0-255 代价图   SeedImage 种子点 标签从1开始
	WaterShedNew(dis, SeedImage, pDst, iDim, pMask_2_3, num); //将平滑后的距离图换成之前的距离图
	writeData(pDst, gFileName + "pDst.raw",iDim);



	// 给尾叶赋标签
	for(int i=0;i<len;i++)
	{
		for(int j=0;j<seedpoints.size();j++)
		{
		  if(pDst[i] == pDst[seedpoints[j]])
		    pMask_2_3[i]=LIVER_8SEGMENT_PART9;
		}
	}
	
	delete[]pSrc;
	delete[]pDst;
	delete[]SeedImage;

	//writeData(pMask_2_3, gFileName+"watershed_3_1.raw",iDim);

	delete[]dis;
	delete[]greyData;
	delete[]result;
  
}
//void SegFunction::seg_CaudateLobe_manual_cut(char *pMask_2_3, int *iTranOriginal, const int *iDim)
//{
//	int len = iDim[0] * iDim[1] * iDim[2];
//	int pageSize = iDim[0] * iDim[1];
//	int *dis = new int[len];
//	memset(dis, 0, len * sizeof(int)); // dis内容全部置0
//	
//	int pointa[3]={209,215,494};  //237,230,250  原图坐标
//	int pointb[3]={216,237,494}; //手工在肝上切割的一条线
//	int tempPoint[3]={0,0,0};
//	for(int i=0;i<len;i++)
//	{
//		  tempPoint[2] = i / pageSize;                //z
//		  tempPoint[1] = i % pageSize / iDim[0];      //y
//		  tempPoint[0] = i % iDim[0];                //x
//		  if(pointToLine(tempPoint,pointa,pointb, iTranOriginal)<3) 
//			  pMask_2_3[i]=0;
//	}
//
//	 // 计算并输出距离图
//	DisGraph(pMask_2_3, dis, iDim);
//	writeData(dis,gFileName + "tranDisGraph_manual.raw",iDim);
//
//	// 求出最大最小距离
//	int min = dis[0];
//	int max = dis[0];
//	for(int i = 1; i < len; i++)
//	{
//	  if(dis[i] < min) 
//		  min = dis[i];
//	  else if(dis[i] > max) 
//		  max = dis[i];
//	}
//
//	// 计算灰度图
//	float *greyData = new float[len];
//	for(int i = 0; i < len; i++)
//	{
//	   greyData[i] = dis[i] * 255 / (max - min);
//	   //result[i]=greyData[i];
//	}
//	//writeData(greyData, gFileName + "greyData.raw", iDim);
//
//
//	//针对灰度图进行高斯平滑
//	 float *result = new float[len];
//	 int Ng = 3;//static_cast<int>(ceil(fNgParm*std_Gb))+1; //fNgParm 6   std_Gb 1
//	 std_Gb = 1 * fStdGbParm / fNorm; //fStdGbParm 3  fNorm 3
//	 Gaussian_3D(result, Ng, std_Gb, greyData, iDim);
//	 //writeData(result,"E:\\ChenCongmei\\pingHua.raw",iDim);
//	 
//
//	 //寻找距离肝静脉分叉点和门脉分叉点连线最近的极大值点
//	 int tempPos=0;
//	 int searchResult[3];
//	 int mindisPoint[3]; //保存 距离肝静脉分叉点和门脉分叉点连线最近的极大值点
//	 double distance;
//	 int flag=0;
//	 std::queue<Point3D<int>> Q;
//	 vector<double> tempDistace;
//	 unsigned char * SeedImage=new unsigned char[len];
//	 memset(SeedImage,0,sizeof(unsigned char)*len);
//	 int num=0;
//
//	 vector<int> seedpoints;
//
//	 for(int i=0;i<iDim[2];i++)
//		 for(int j=0;j<iDim[1];j++)
//			 for(int k=0;k<iDim[0];k++)
//	           {
//	             if((result[tempPos]>0) && maxPoint(result,k,j,i,iDim)) 
//				 {
//                   searchResult[0]=k;
//				   searchResult[1]=j;
//				   searchResult[2]=i;
//				   double tempdis = pointToLine(searchResult,veinPoint,portalPoint, iTranOriginal); // veinPoint（下腔静脉血管点） portalPoint（门脉血管点）在原始图像中手工选取
//				   if(tempdis<34)
//					   seedpoints.push_back(tempPos);
//				   num++;
//				   SeedImage[tempPos]=num;
//				   Q.push(Point3D<int>(searchResult[0],searchResult[1],searchResult[2]));
//				   tempDistace.push_back(tempdis);
//				 }
//				 tempPos++;
//	           }
//
//    unsigned char *pSrc=new unsigned char[len];
//	char *pDst=new char[len];
//	for(int i=0;i<len;i++)
//	{
//	  if(result[i]>255) pSrc[i]=255;
//	  else
//		  pSrc[i]=static_cast<unsigned char>(int(result[i]));
//
//	  //if(result[i]>0) SeedImage[i]=1;
//	}
//	//pSrc归一化到0-255 代价图   SeedImage 种子点 标签从1开始
//	WaterShedNew(dis, SeedImage, pDst, iDim, pMask_2_3, num); //将平滑后的距离图换成之前的距离图
//	//writeData(pDst, "E:\\ChenCongmei\\pDst.raw",iDim);
//
//	// 给尾叶赋标签
//	for(int i=0;i<len;i++)
//	{
//		for(int j=0;j<seedpoints.size();j++)
//		{
//		  if(pDst[i]==pDst[seedpoints[j]])
//		    pMask_2_3[i]=LIVER_8SEGMENT_PART9;
//		}
//	}
//	
//	delete[]pSrc;
//	delete[]pDst;
//	delete[]SeedImage;
//
//	writeData(pMask_2_3,gFileName+"/watershed_3_1.raw",iDim);
//
//	delete[]dis;
//	delete[]greyData;
//	delete[]result;
//  
//}
//运用腐蚀方法进行分割肝尾叶
//void SegFunction::seg_CaudateLobe(char *pAllMask,const int *iDim) //分割尾叶
//{
//	int len=iDim[0]*iDim[1]*iDim[2];
//	char *initMask=new char[len]; 
//	char *flag=new char[len]; //只腐蚀肝脏LIVER_8SEGMENT_PART2和LIVER_8SEGMENT_PART3
//	memcpy(flag,pAllMask,len*sizeof(char));
//	memcpy(initMask,pAllMask,len*sizeof(char));
//	int sign=1;
//	int change=0;
//	char *temp=new char[len];
//	
//	while(sign)//循环腐蚀，直至断开
//	{
//	  
//	  corrosion(pAllMask,flag,LIVER_8SEGMENT_PART2,LIVER_8SEGMENT_PART3,iDim);
//	  //writeData(flag,"F://CentreLine2//HIU16//03_LiuHaiSheng//test.raw",iDim);
//	  memcpy(pAllMask,flag,len*sizeof(char));
//	  memcpy(temp,pAllMask,len*sizeof(char));
//	  sign=is_connect(pAllMask,temp,LIVER_8SEGMENT_PART2,LIVER_8SEGMENT_PART3,iDim,change);
//	}
//	//temp mask1和mask2   pAllMask 肝二段和肝三段 标签不一样，都是腐蚀的结果
//	std::queue<int> large;
//	std::queue<int> CLobe;
//	  int *LDistance=new int[len]; 
//	  int *CDistance=new int[len];  //记录图像中点到肝尾叶的最短距离
//	  memset(LDistance,127,sizeof(int)*len);  //距离均初始化为最大值,了解memset的不同初始化测试
//	  memset(CDistance,127,sizeof(int)*len); //初始化为 二进制00000001 00000001 00000001 00000001
//	 if(change==0)
//	 {
//	  for(int i=0;i<len;i++)
//	  {
//			 if(temp[i]==tempMark1)
//				{
//					temp[i]=LIVER_8SEGMENT_PART9;
//					CLobe.push(i);
//					CDistance[i]=0;
//				}
//			  if(temp[i]==tempMark2)
//				{
//					large.push(i);
//					LDistance[i]=0;
//				}
//	  }
//	 }
//	 else 
//	 {
//	   for(int i=0;i<len;i++)
//	  {
//			 if(temp[i]==tempMark2)
//				{
//					temp[i]=LIVER_8SEGMENT_PART9;
//					CLobe.push(i);
//					CDistance[i]=0;
//				}
//			  if(temp[i]==tempMark1)
//				{
//					large.push(i);
//					LDistance[i]=0;
//				}
//	  }
//	 }
//	//writeData(initMask,"F://CentreLine2//HIU16//03_LiuHaiSheng//initMask.raw",iDim);
//	
//	//writeData(LDistance,"F://CentreLine2//HIU16//03_LiuHaiSheng//LDistance1.raw",iDim);
//	//writeData(CDistance,"F://CentreLine2//HIU16//03_LiuHaiSheng//CDistance.raw",iDim);
//    calDistance(&large,LDistance,initMask,temp,iDim);
//	//writeData(LDistance,"F://CentreLine2//HIU16//03_LiuHaiSheng//LDistance2.raw",iDim);
//	calDistance(&CLobe,CDistance,initMask,temp,iDim);
//	//writeData(temp,"F://CentreLine2//HIU16//03_LiuHaiSheng//temp1.raw",iDim);
//	for(int i=0;i<len;i++)
//	{
//	  if((initMask[i]==LIVER_8SEGMENT_PART2 || initMask[i]==LIVER_8SEGMENT_PART3) && temp[i]==0)
//	  {
//	    if(LDistance[i]>CDistance[i]) temp[i]=LIVER_8SEGMENT_PART9;
//	  }
//	}
//	//writeData(temp,"F://CentreLine2//HIU16//03_LiuHaiSheng//temp2.raw",iDim);
//	//writeData(initMask,"F://CentreLine2//HIU16//03_LiuHaiSheng//initMask1.raw",iDim);
//	for(int i=0;i<len;i++)
//	{
//	  if(temp[i]==LIVER_8SEGMENT_PART9)
//		  initMask[i]=LIVER_8SEGMENT_PART9;
//	}
//	memcpy(pAllMask,initMask,len*sizeof(char));
//	//writeData(initMask,"F://CentreLine2//HIU16//03_LiuHaiSheng//initMask2.raw",iDim);
//	delete []initMask;
//	delete[]flag;
//	delete[]temp;
//	delete[]LDistance;
//	delete[]CDistance;
//}

//void SegFunction:: corrosion(char *afterFlag,char *flag,int mark1,int mark2,const int *iDim)
//  {
//	  int lFrameSize=iDim[0]*iDim[1];   
//	  int maxSize=iDim[0]*iDim[1]*iDim[2];  
//	  int cubeSize=1;
//	  for(int i=0;i<iDim[2];i++)
//		   {
//			   for(int j=0;j<iDim[1];j++)
//			   {
//				   for(int k=0;k<iDim[0];k++)
//				   {
//							int process=false;
//							if(afterFlag[i*lFrameSize+j*iDim[0]+k]==mark1 || afterFlag[i*lFrameSize+j*iDim[0]+k]==mark2)
//							{
//							   for(int m=i-cubeSize;m<=i+cubeSize;m++)
//							   {
//								   for(int n=j-cubeSize;n<=j+cubeSize;n++)
//								   {
//									   for(int l=k-cubeSize;l<=k+cubeSize;l++)
//									   {
//										   int t=m*lFrameSize+n*iDim[0]+l;
//										 if(t<maxSize && afterFlag[t]!=mark1 && t<maxSize && afterFlag[t]!=mark2)
//										 {
//										   process=true;//种子点周围有非肺的点，下一步需要将整个立方体中的点变为非肺点
//										   break;
//										 }
//									   }
//									   if(process)
//										   break;
//								   }
//								    if(process)
//										   break;
//								}
//								if(process)
//								{
//								  for(int m=i-cubeSize;m<=i+cubeSize;m++)
//								  {
//								    for(int n=j-cubeSize;n<=j+cubeSize;n++)
//									{
//									   for(int l=k-cubeSize;l<=k+cubeSize;l++)
//									   {
//										 int t=m*lFrameSize+n*iDim[0]+l;
//										 if(t<maxSize)
//										 {
//										   flag[t]=0;
//										 }
//									   }
//									}
//								  }
//								}
//						   }
//				   }
//			   }
//		   }
//  }


void SegFunction:: corrosion(char *afterFlag,char *flag,int mark1,int mark2,const int *iDim)
  {
	  int lFrameSize=iDim[0]*iDim[1];   
	  int maxSize=iDim[0]*iDim[1]*iDim[2];  
	  int cubeSize=1;
	  for(int i=0;i<iDim[2];i++)
		   {
			   for(int j=0;j<iDim[1];j++)
			   {
				   for(int k=0;k<iDim[0];k++)
				   {
							int process=false;
							if(afterFlag[i*lFrameSize+j*iDim[0]+k]==mark1 || afterFlag[i*lFrameSize+j*iDim[0]+k]==mark2)
							{
							   for(int m=i-cubeSize;m<=i+cubeSize;m++)
							   {
								   for(int n=j-cubeSize;n<=j+cubeSize;n++)
								   {
									   for(int l=k-cubeSize;l<=k+cubeSize;l++)
									   {
										   int t=m*lFrameSize+n*iDim[0]+l;
										 if(t<maxSize && afterFlag[t]!=mark1 && t<maxSize && afterFlag[t]!=mark2)
										 {
										   process=true;//种子点周围有非肝二段或肝三段的点
										   break;
										 }
									   }
									   if(process)
										   break;
								   }
								    if(process)
										   break;
								}
							 if(process) flag[i*lFrameSize+j*iDim[0]+k]=0;
						   }
				   }
			   }
		   }
  }

bool SegFunction:: is_connect(char *mask,char *temp,int mark1,int mark2,const int *iDim,int &change)
{
	int len=iDim[0]*iDim[1]*iDim[2];
	int lFrameSize=iDim[0]*iDim[1];   
	
	//记录区域增长种子点的坐标
	int seed_x=0;
	int seed_y=0;
	int seed_z=0;
	int flag=0;
	 for(int i=0;i<iDim[2];i++)
		   {
			   for(int j=0;j<iDim[1];j++)
			   {
				   for(int k=0;k<iDim[0];k++)
				   {
					   if(mask[i*lFrameSize+j*iDim[0]+k]==mark1 || mask[i*lFrameSize+j*iDim[0]+k]==mark2)
					   {
					      seed_x=k;
						  seed_y=j;
						  seed_z=i;
						  flag=1;
						  break;
					   }
				   }
				   if(flag) break;
			   }
			   if(flag) break;
	 }
	 std::queue<Point3D<int>>Q;
	 Q.push(Point3D<int>(seed_x,seed_y,seed_z));
	 int *pMatrix=new int[len]; //用于标记点有没有被访问
	 int m;
	 memset(pMatrix,0,sizeof(int)*len); 
	 int curPos[3];
	 int count1=1;
	 int count2=0;
	while (!Q.empty())
		{
			//区域增长不选择斜点增长。即只增长上、下、左、右、前、后
			Point3D<int> &cur=Q.front();
	        m=cur.z*lFrameSize+cur.y*iDim[0]+cur.x;
			//printf("%d",afterFlag[m]);
			temp[m]=TEMPMARK1;
			count1++;
			int a=cur.x;
			//printf("%d",a);
			
			if(cur.x-1>0&&cur.x+1<iDim[0]&&cur.y-1>0&&cur.y+1<iDim[1]&&cur.z>0&&cur.z+1<iDim[2])
			{
				curPos[0]=cur.x-1;
				curPos[1]=cur.y;
				curPos[2]=cur.z;
			    m=curPos[2]*lFrameSize+curPos[1]*iDim[0]+curPos[0];
				if((temp[m]==mark1||temp[m]==mark2) && pMatrix[m]==0){  //此点是肺且没有被访问过
					Q.push(Point3D<int>(curPos[0],curPos[1],curPos[2]));
					pMatrix[m]=1; //表示此点已被访问
				}

				curPos[0]=cur.x+1;
				curPos[1]=cur.y;
				curPos[2]=cur.z;
			    m=curPos[2]*lFrameSize+curPos[1]*iDim[0]+curPos[0];
				if((temp[m]==mark1||temp[m]==mark2) && pMatrix[m]==0){
					Q.push(Point3D<int>(curPos[0],curPos[1],curPos[2]));
					pMatrix[m]=1; //表示此点已被访问
				}
				

				curPos[0]=cur.x;
				curPos[1]=cur.y-1;
				curPos[2]=cur.z;
			    m=curPos[2]*lFrameSize+curPos[1]*iDim[0]+curPos[0];
				if((temp[m]==mark1||temp[m]==mark2) && pMatrix[m]==0){
					Q.push(Point3D<int>(curPos[0],curPos[1],curPos[2]));
					pMatrix[m]=1; //表示此点已被访问
				}

				curPos[0]=cur.x;
				curPos[1]=cur.y+1;
				curPos[2]=cur.z;
			    m=curPos[2]*lFrameSize+curPos[1]*iDim[0]+curPos[0];
				if((temp[m]==mark1||temp[m]==mark2) && pMatrix[m]==0){
					Q.push(Point3D<int>(curPos[0],curPos[1],curPos[2]));
					pMatrix[m]=1; //表示此点已被访问
				}

				curPos[0]=cur.x;
				curPos[1]=cur.y;
				curPos[2]=cur.z-1;
			    m=curPos[2]*lFrameSize+curPos[1]*iDim[0]+curPos[0];
				if((temp[m]==mark1||temp[m]==mark2) && pMatrix[m]==0){
					Q.push(Point3D<int>(curPos[0],curPos[1],curPos[2]));
					pMatrix[m]=1; //表示此点已被访问
				}

				curPos[0]=cur.x;
				curPos[1]=cur.y;
				curPos[2]=cur.z+1;
			    m=curPos[2]*lFrameSize+curPos[1]*iDim[0]+curPos[0];
				if((temp[m]==mark1||temp[m]==mark2) && pMatrix[m]==0){
					Q.push(Point3D<int>(curPos[0],curPos[1],curPos[2]));
					pMatrix[m]=1; //表示此点已被访问
				}
			}
			
		    Q.pop();
		}

	//string str="F://CentreLine2//HIU16//03_LiuHaiSheng//03_LiuHaiSheng.txt";
	//str.erase(str.find_last_of('/')+1);
	//str=str+"test_is_con_mask.raw";
	//FILE *fp;
	//fp=fopen(str.c_str(),"wb");
	///*fwrite(temp,sizeof(unsigned char),len,fp);*/
	//fwrite(temp,sizeof(unsigned char),len,fp);
	//fclose(fp);

	//
	 for(int i=0;i<iDim[2];i++)
		   {
			   for(int j=0;j<iDim[1];j++)
			   {
				   for(int k=0;k<iDim[0];k++)
				   {
					   if(temp[i*lFrameSize+j*iDim[0]+k]==mark1 || temp[i*lFrameSize+j*iDim[0]+k]==mark2)
					   {
					      //return false; //表示不联通
						   temp[i*lFrameSize+j*iDim[0]+k]=TEMPMARK2;
						   count2++;
					   }
				   }
				   
			   }
	 }
    //writeData(mask,"F://CentreLine2//HIU16//03_LiuHaiSheng//test_is_con_mask.raw",iDim);
 	
	if(count2<100) return true;
	else
	{
		if(count1<count2) change=0;
		else change=1;
		return false;
	}
	//return true;//表示联通
}

//
//void SegFunction::writeData(char *mask,string name,const int *iDim)
//{
//	int len=iDim[0]*iDim[1]*iDim[2];
//	FILE *fp;
//	fp=fopen(name.c_str(),"wb");
//	fwrite(mask,sizeof(char),len,fp);
//	fclose(fp);
//}
//
//void SegFunction::writeData(unsigned char *mask,string name,const int *iDim)
//{
//	int len=iDim[0]*iDim[1]*iDim[2];
//	FILE *fp;
//	fp=fopen(name.c_str(),"wb");
//	fwrite(mask,sizeof(unsigned char),len,fp);
//	fclose(fp);
//}
//
//void SegFunction::writeData(int *mask,string name,const int *iDim)
//{
//	int len=iDim[0]*iDim[1]*iDim[2];
//	FILE *fp;
//	fp=fopen(name.c_str(),"wb");
//	fwrite(mask,sizeof(int),len,fp);
//	fclose(fp);
//}
//
//void SegFunction::writeData(float *mask,string name,const int *iDim)
//{
//	int len=iDim[0]*iDim[1]*iDim[2];
//	FILE *fp;
//	fp=fopen(name.c_str(),"wb");
//	fwrite(mask,sizeof(float),len,fp);
//	fclose(fp);
//}
//
//void SegFunction::writeData(short *mask,string name,const int *iDim)
//{
//	int len=iDim[0]*iDim[1]*iDim[2];
//	FILE *fp;
//	fp=fopen(name.c_str(),"wb");
//	fwrite(mask,sizeof(short),len,fp);
//	fclose(fp);
//}

template<typename T>
void SegFunction::writeData(T *mask, string name, const int *iDim)
{
	int len=iDim[0]*iDim[1]*iDim[2];
	FILE *fp;
	fp=fopen(name.c_str(),"wb");
	fwrite(mask,sizeof(T),len,fp);
	fclose(fp);
}

void SegFunction::calDistance(std::queue<int> *leftS,int *lDistance,char *afterFlag,char *flag,const int *iDim)
	{
		int maxSize=iDim[0]*iDim[1]*iDim[2];
		int pageSize=iDim[0]*iDim[1];
		int *laber=new int[maxSize];
		memset(laber,0,sizeof(int)*maxSize);
		//int Oldposition;
		int Newposition;
		//int distance;
		while(!leftS->empty())
	   {
	     int Oldposition=leftS->front(); 
		  //只扫描Oldposition的上下左右前后，则Newposition到Oldposition的距离均为1
		
		    Newposition=Oldposition-pageSize; //上
			if(Newposition>0 && (afterFlag[Newposition]==LIVER_8SEGMENT_PART2 || afterFlag[Newposition]==LIVER_8SEGMENT_PART3) && flag[Newposition]==0 && laber[Newposition]==0)
			{
			  if(lDistance[Oldposition]+1<lDistance[Newposition]) //则此点加入集合leftS
					   {
						   lDistance[Newposition]=lDistance[Oldposition]+1; //更新距离
						   leftS->push(Newposition);
					   }
			}

			Newposition=Oldposition+pageSize; //下
			if(Newposition<maxSize && (afterFlag[Newposition]==LIVER_8SEGMENT_PART2 || afterFlag[Newposition]==LIVER_8SEGMENT_PART3) && flag[Newposition]==0 && laber[Newposition]==0)
			{
			  if(lDistance[Oldposition]+1<lDistance[Newposition]) //则此点加入集合leftS
					   {
						   lDistance[Newposition]=lDistance[Oldposition]+1; //更新距离
						   leftS->push(Newposition);
					   }
			}

			Newposition=Oldposition-1; //左
			if(Newposition>0 && (afterFlag[Newposition]==LIVER_8SEGMENT_PART2 || afterFlag[Newposition]==LIVER_8SEGMENT_PART3) && flag[Newposition]==0 && laber[Newposition]==0)
			{
			  if(lDistance[Oldposition]+1<lDistance[Newposition]) //则此点加入集合leftS
					   {
						   lDistance[Newposition]=lDistance[Oldposition]+1; //更新距离
						   leftS->push(Newposition);
					   }
			}

			Newposition=Oldposition+1; //右
			if(Newposition<maxSize && (afterFlag[Newposition]==LIVER_8SEGMENT_PART2 || afterFlag[Newposition]==LIVER_8SEGMENT_PART3) && flag[Newposition]==0 && laber[Newposition]==0)
			{
			  if(lDistance[Oldposition]+1<lDistance[Newposition]) //则此点加入集合leftS
					   {
						   lDistance[Newposition]=lDistance[Oldposition]+1; //更新距离
						   leftS->push(Newposition);
					   }
			}

			Newposition=Oldposition-iDim[0]; //前
			if(Newposition>0 && (afterFlag[Newposition]==LIVER_8SEGMENT_PART2 || afterFlag[Newposition]==LIVER_8SEGMENT_PART3) && flag[Newposition]==0 && laber[Newposition]==0)
			{
			  if(lDistance[Oldposition]+1<lDistance[Newposition]) //则此点加入集合leftS
					   {
						   lDistance[Newposition]=lDistance[Oldposition]+1; //更新距离
						   leftS->push(Newposition);
					   }
			}

			Newposition=Oldposition+iDim[0]; //后
			if(Newposition<maxSize && (afterFlag[Newposition]==LIVER_8SEGMENT_PART2 || afterFlag[Newposition]==LIVER_8SEGMENT_PART3) && flag[Newposition]==0 && laber[Newposition]==0)
			{
			  if(lDistance[Oldposition]+1<lDistance[Newposition]) //则此点加入集合leftS
					   {
						   lDistance[Newposition]=lDistance[Oldposition]+1; //更新距离
						   leftS->push(Newposition);
					   }
			}
		

	
		 //寻找6领域后对当前Oldposition点进行标记
		 laber[Oldposition]=1;
		 leftS->pop();
	   }
		delete[]laber;

	}

//void SegFunction::DisGraph(char *mask,int *dis,const int *iDim)
//{
//  int len=iDim[0]*iDim[1]*iDim[2];
//  int pageSize=iDim[0]*iDim[1];
//  int *flag=new int[len];
//  memset(flag,0,len*sizeof(char));
//  int newPosition;
//  int min;
//  for(int i=0;i<len;i++)
//  {
//    if(mask[i]!=blank && flag[i]==0)//flag[i]==0表示此点没有被访问
//	{
//	   min=
//	   newPosition=i+pageSize;
//	   if(newPosition<len && dis[newPosition]<min) min=dis[newPosition];
//	   newPosition=i-pageSize;
//	   if(newPosition>=0 && dis[newPosition]<min) min=dis[newPosition];
//	   newPosition=i+iDim[0];
//	   if(newPosition<len && dis[newPosition]<min) min=dis[newPosition];
//	   newPosition=i-iDim[0];
//	   if(newPosition>=0 && dis[newPosition]<min) min=dis[newPosition];
//	   newPosition=i+1;
//	   if(newPosition<len && dis[newPosition]<min) min=dis[newPosition];
//	   newPosition=i-1;
//	   if(newPosition>=0 && dis[newPosition]<min) min=dis[newPosition];
//	   dis[i]=min+1;
//	   flag[i]=1;
//	}
//	
//  }
//  delete[]flag;
//}

	void SegFunction::DisGraph(char *mask, int *dis, const int *iDim)
	{
	  int len=iDim[0]*iDim[1]*iDim[2];
	  int pageSize=iDim[0]*iDim[1];
	  int *flag=new int[len];
	  memset(flag,0,len*sizeof(int));
	  int newPosition;
	  int min;
	  int stop=0;
	  int distance=1;
	  const int minDis=1;
	  for(int i=0;i<len;i++)
	  {
		if(mask[i]!=blank && roundValue(mask,i,blank,iDim))
		{
			dis[i]=minDis;
			flag[i]=1; //表示访问过
		}
	  }
	  // writeData(dis,"F://CentreLine2//HIU16//03_LiuHaiSheng//testDis.raw",iDim);
	  // writeData(flag,"F://CentreLine2//HIU16//03_LiuHaiSheng//flag.raw",iDim);
	  while(!stop)
	  {
		 stop=1;
			  for(int i=0;i<len;i++)
			  {
				if(mask[i]!=blank && flag[i]==0 && roundValue(dis,i,distance,iDim))//flag[i]==0表示此点没有被访问
				{
				  dis[i]=distance+1;
				  flag[i]=1;
				  stop=0;
			    }
			  }
	   distance++;
	   //writeData(dis,"F://CentreLine2//HIU16//06_LingMengMeng//testDis_18_5.raw",iDim);
	  }
	  delete[]flag;
	}

	bool SegFunction::roundValue(char *mask,int position,int value,const int *iDim)//判断position周围有没有值value
    {
      int len=iDim[0]*iDim[1]*iDim[2];
	  int pageSize=iDim[0]*iDim[1];
	  int newPosition;
		newPosition=position+pageSize;
		if(newPosition<len && mask[newPosition]==value) return true;
		
	    newPosition=position-pageSize;
		if(newPosition>=0 && mask[newPosition]==value) return true;
		
		newPosition=position+iDim[0];
		if(newPosition<len && mask[newPosition]==value) return true;
		
		newPosition=position-iDim[0];
		if(newPosition>=0 && mask[newPosition]==value) return true;
		
		newPosition=position+1;
		if(newPosition<len && mask[newPosition]==value) return true;
		
		newPosition=position-1;
		if(newPosition>=0 && mask[newPosition]==value) return true;

		//考虑再增加12个方向
		newPosition=position+pageSize+iDim[0];
		if(newPosition<len && mask[newPosition]==value) return true;
		
		newPosition=position+pageSize-iDim[0];
		if(newPosition<len && mask[newPosition]==value) return true;
		
		newPosition=position+pageSize+1;
		if(newPosition<len && mask[newPosition]==value) return true;
		
		newPosition=position+pageSize-1;
		if(newPosition<len && mask[newPosition]==value) return true;

		newPosition=position-pageSize+iDim[0];
		if(newPosition>=0 && mask[newPosition]==value) return true;
		
		newPosition=position-pageSize-iDim[0];
		if(newPosition>=0 && mask[newPosition]==value) return true;
		
		newPosition=position-pageSize+1;
		if(newPosition>=0 && mask[newPosition]==value) return true;
		
		newPosition=position-pageSize-1;
		if(newPosition>=0 && mask[newPosition]==value) return true;

		newPosition=position+iDim[0]+1;
		if(newPosition<len && mask[newPosition]==value) return true;

		newPosition=position+iDim[0]-1;
		if(newPosition<len && mask[newPosition]==value) return true;

		newPosition=position-iDim[0]+1;
		if(newPosition>0 &&newPosition<len && mask[newPosition]==value) return true;

		newPosition=position-iDim[0]-1;
		if(newPosition>0 &&newPosition<len && mask[newPosition]==value) return true;
		return false;
     }

	bool SegFunction::roundValue(int *dis,int position,int value,const int *iDim)//判断position周围有没有值value
    {
      int len=iDim[0]*iDim[1]*iDim[2];
	  int pageSize=iDim[0]*iDim[1];
	  int newPosition;
		newPosition=position+pageSize;
		if(newPosition<len && dis[newPosition]==value) return true;
		
	    newPosition=position-pageSize;
		if(newPosition>=0 && dis[newPosition]==value) return true;
		
		newPosition=position+iDim[0];
		if(newPosition<len && dis[newPosition]==value) return true;
		
		newPosition=position-iDim[0];
		if(newPosition>=0 && dis[newPosition]==value) return true;
		
		newPosition=position+1;
		if(newPosition<len && dis[newPosition]==value) return true;
		
		newPosition=position-1;
		if(newPosition>=0 && dis[newPosition]==value) return true;

		//新增12个方向
		newPosition=position+pageSize+iDim[0];
		if(newPosition<len && dis[newPosition]==value) return true;
		
		newPosition=position+pageSize-iDim[0];
		if(newPosition<len && dis[newPosition]==value) return true;
		
		newPosition=position+pageSize+1;
		if(newPosition<len && dis[newPosition]==value) return true;
		
		newPosition=position+pageSize-1;
		if(newPosition<len && dis[newPosition]==value) return true;

		newPosition=position-pageSize+iDim[0];
		if(newPosition>=0 && dis[newPosition]==value) return true;
		
		newPosition=position-pageSize-iDim[0];
		if(newPosition>=0 && dis[newPosition]==value) return true;
		
		newPosition=position-pageSize+1;
		if(newPosition>=0 && dis[newPosition]==value) return true;
		
		newPosition=position-pageSize-1;
		if(newPosition>=0 && dis[newPosition]==value) return true;

		newPosition=position+iDim[0]+1;
		if(newPosition<len && dis[newPosition]==value) return true;

		newPosition=position+iDim[0]-1;
		if(newPosition<len && dis[newPosition]==value) return true;

		newPosition=position-iDim[0]+1;
		if(newPosition>0 && newPosition<len && dis[newPosition]==value) return true;

		newPosition=position-iDim[0]-1;
		if(newPosition>0 && newPosition<len && dis[newPosition]==value) return true;
		return false;
     }

	bool SegFunction::maxPoint(float *result,int x,int y,int z,const int *iDim)//判断position是否为极大值点
    {
      int len=iDim[0]*iDim[1]*iDim[2];
	  int pageSize=iDim[0]*iDim[1];
	  int newX;
	  int newY;
	  int newZ;
	  int position=z*pageSize+y*iDim[0]+x;
	  int newPosition;

	    newPosition=position+pageSize;
		if(z==iDim[2]-1 || (newPosition<len && result[newPosition]>=result[position])) return false;
		
	    newPosition=position-pageSize;
		if(z==0 || (newPosition>=0 && result[newPosition]>=result[position])) return false;
		
		newPosition=position+iDim[0];
		if(y==iDim[1]-1 || (newPosition<len && result[newPosition]>=result[position])) return false;
		
		newPosition=position-iDim[0];
		if(y==0 || (newPosition>=0 && result[newPosition]>=result[position])) return false;
		
		newPosition=position+1;
		if(x==iDim[0]-1 || (newPosition<len && result[newPosition]>=result[position])) return false;
		
		newPosition=position-1;
		if(x==0 || (newPosition>=0 && result[newPosition]>=result[position])) return false;

		//新增加12 下一层
		newPosition=position+pageSize+iDim[0];
		if(z==iDim[2]-1 ||y==iDim[1]-1 || (newPosition<len && result[newPosition]>=result[position])) return false;
		
		newPosition=position+pageSize-iDim[0];
		if(z==iDim[2]-1 ||y==0 || (newPosition>=0 && result[newPosition]>=result[position])) return false;
		
		newPosition=position+pageSize+1;
		if(z==iDim[2]-1 ||x==iDim[0]-1 || (newPosition<len && result[newPosition]>=result[position])) return false;
		
		newPosition=position+pageSize-1;
		if(z==iDim[2]-1 ||x==0 || (newPosition>=0 && result[newPosition]>=result[position])) return false;

		//上一层
		newPosition=position-pageSize+iDim[0];
		if(z==0 ||y==iDim[1]-1 || (newPosition<len && result[newPosition]>=result[position])) return false;
		
		newPosition=position-pageSize-iDim[0];
		if(z==0 ||y==0 || (newPosition>=0 && result[newPosition]>=result[position])) return false;
		
		newPosition=position-pageSize+1;
		if(z==0 ||x==iDim[0]-1 || (newPosition<len && result[newPosition]>=result[position])) return false;
		
		newPosition=position-pageSize-1;
		if(z==0 ||x==0 || (newPosition>=0 && result[newPosition]>=result[position])) return false;

		//本层
		newPosition=position+iDim[0]+1;
		if(x==iDim[0]-1 ||y==iDim[1]-1 || (newPosition<len && result[newPosition]>=result[position])) return false;
		
		newPosition=position-iDim[0]+1;
		if(x==iDim[0]-1 ||y==0 || (newPosition>=0 && result[newPosition]>=result[position])) return false;
		
		newPosition=position+iDim[0]-1;
		if(x==0 ||y==iDim[1]-1|| (newPosition<len && result[newPosition]>=result[position])) return false;
		
		newPosition=position-iDim[0]-1;
		if(x==0 ||y==0 || (newPosition>=0 && result[newPosition]>=result[position])) return false;
		return true;
     }

	bool SegFunction::minPoint(float *result,int x,int y,int z,const int *iDim)//判断position是否为极小值点
    {
      int len=iDim[0]*iDim[1]*iDim[2];
	  int pageSize=iDim[0]*iDim[1];
	  int newX;
	  int newY;
	  int newZ;
	  int position=z*pageSize+y*iDim[0]+x;
	  int newPosition;

	    newPosition=position+pageSize;
		if(z==iDim[2]-1 || (newPosition<len && result[newPosition]<=result[position])) return false;
		
	    newPosition=position-pageSize;
		if(z==0 || (newPosition>=0 && result[newPosition]<=result[position])) return false;
		
		newPosition=position+iDim[0];
		if(y==iDim[1]-1 || (newPosition<len && result[newPosition]<=result[position])) return false;
		
		newPosition=position-iDim[0];
		if(y==0 || (newPosition>=0 && result[newPosition]<=result[position])) return false;
		
		newPosition=position+1;
		if(x==iDim[0]-1 || (newPosition<len && result[newPosition]<=result[position])) return false;
		
		newPosition=position-1;
		if(x==0 || (newPosition>=0 && result[newPosition]<=result[position])) return false;

		//新增加12 下一层
		//newPosition=position+pageSize+iDim[0];
		//if(z==iDim[2]-1 ||y==iDim[1]-1 || (newPosition<len && result[newPosition]<=result[position])) return false;
		//
		//newPosition=position+pageSize-iDim[0];
		//if(z==iDim[2]-1 ||y==0 || (newPosition>=0 && result[newPosition]<=result[position])) return false;
		//
		//newPosition=position+pageSize+1;
		//if(z==iDim[2]-1 ||x==iDim[0]-1 || (newPosition<len && result[newPosition]<=result[position])) return false;
		//
		//newPosition=position+pageSize-1;
		//if(z==iDim[2]-1 ||x==0 || (newPosition>=0 && result[newPosition]<=result[position])) return false;

		////上一层
		//newPosition=position-pageSize+iDim[0];
		//if(z==0 ||y==iDim[1]-1 || (newPosition<len && result[newPosition]<=result[position])) return false;
		//
		//newPosition=position-pageSize-iDim[0];
		//if(z==0 ||y==0 || (newPosition>=0 && result[newPosition]<=result[position])) return false;
		//
		//newPosition=position-pageSize+1;
		//if(z==0 ||x==iDim[0]-1 || (newPosition<len && result[newPosition]<=result[position])) return false;
		//
		//newPosition=position-pageSize-1;
		//if(z==0 ||x==0 || (newPosition>=0 && result[newPosition]<=result[position])) return false;

		////本层
		//newPosition=position+iDim[0]+1;
		//if(x==iDim[0]-1 ||y==iDim[1]-1 || (newPosition<len && result[newPosition]<=result[position])) return false;
		//
		//newPosition=position-iDim[0]+1;
		//if(x==iDim[0]-1 ||y==0 || (newPosition>=0 && result[newPosition]<=result[position])) return false;
		//
		//newPosition=position+iDim[0]-1;
		//if(x==0 ||y==iDim[1]-1|| (newPosition<len && result[newPosition]<=result[position])) return false;
		//
		//newPosition=position-iDim[0]-1;
		//if(x==0 ||y==0 || (newPosition>=0 && result[newPosition]<=result[position])) return false;
		return true;
     }

	
	/*
	 *  Function：     求点到直线的距离
	 *	point：        点
	 *  start, end：   起点终点连成连线
	 *  iTranOriginal: 变换后图像的原点 （可将坐标映射回原始图像）
	 *
	 *  Tips:先将point映射回原始图像再计算（由于start, end为原始图像的点）
	 *
	 */
	double SegFunction::pointToLine(int *point,int *start,int *end, int *iTranOriginal)
	{
       int a[3];
	   int b[3];
	   int *pointOriginal = new int[3];
	   pointOriginal[0] = point[0] + iTranOriginal[0];
	   pointOriginal[1] = point[1] + iTranOriginal[1];
	   pointOriginal[2] = point[2] + iTranOriginal[2];

	   a[0]=pointOriginal[0]-start[0];
	   a[1]=pointOriginal[1]-start[1];
	   a[2]=pointOriginal[2]-start[2];
	   b[0]=start[0]-end[0];
	   b[1]=start[1]-end[1];
	   b[2]=start[2]-end[2];
	   double length1=pow(double(a[1]*b[2]-a[2]*b[1]),2)+pow(double(a[2]*b[0]-a[0]*b[2]),2)+pow(double(a[0]*b[1]-a[1]*b[0]),2);
	   double lenght2=pow(double(b[0]),2)+pow(double(b[1]),2)+pow(double(b[2]),2);
	   return sqrt(length1/lenght2);
	}

	double SegFunction::pointToLine(int *point,int *start,int *end)
	{
       int a[3];
	   int b[3];
	   a[0]=point[0]-start[0];
	   a[1]=point[1]-start[1];
	   a[2]=point[2]-start[2];
	   b[0]=start[0]-end[0];
	   b[1]=start[1]-end[1];
	   b[2]=start[2]-end[2];
	   double length1=pow(double(a[1]*b[2]-a[2]*b[1]),2)+pow(double(a[2]*b[0]-a[0]*b[2]),2)+pow(double(a[0]*b[1]-a[1]*b[0]),2);
	   double lenght2=pow(double(b[0]),2)+pow(double(b[1]),2)+pow(double(b[2]),2);
	   return sqrt(length1/lenght2);
	}

	double SegFunction::pointToPoint2D(int *point,int *portal)
	{
	   double length1=pow(double(point[0]-portal[0]), 2) + pow(double(point[1]-portal[1]), 2);
	   return sqrt(length1);
	}

	double SegFunction::pointToPoint(int *point,int *portal)
	{
	   double length1=pow(double(point[0]-portal[0]),2)+pow(double(point[1]-portal[1]),2)+pow(double(point[2]-portal[2]),2);
	   return sqrt(length1);
	}

	//mask 为平滑后的图像    mask8为分段后的标记
	void SegFunction::GrowOnPoint(float *mask,char *mask8,int *point,const int *iDim)
	{
	  std::queue<Point3D<int>>Q;
	  int len=iDim[0]*iDim[1]*iDim[2];
	  int pageSize=iDim[0]*iDim[1];
	  int *flag=new int[len]; //设立访问标志，0表示未访问，1表示已访问
	  memset(flag,0,sizeof(int)*len);
	  Q.push(Point3D<int>(point[0],point[1],point[2]));
	  flag[point[2]*pageSize+point[1]*iDim[0]+point[0]]=1;
	/*  int newX;
	  int newY;
	  int newZ;*/
	  int position;//=z*pageSize+y*iDim[0]+x;
	  int newPosition;
	  while(!Q.empty()) 
	  {
		  Point3D<int> temp=Q.front();
		  position=temp.z*pageSize+temp.y*iDim[0]+temp.x;

		  newPosition=position+pageSize;
		if(temp.z<iDim[2]-1 && flag[newPosition]==0 && mask8[newPosition]!=blank  && mask[newPosition]<mask[position])//flag==0 表示没有被访问
		{
		  mask8[newPosition]=LIVER_8SEGMENT_PART9;
		  Q.push(Point3D<int>(temp.x,temp.y,temp.z+1)); 
		  flag[newPosition]=1;
		}
		
	    newPosition=position-pageSize;
		if(temp.z>0 && flag[newPosition]==0 && mask8[newPosition]!=blank && mask[newPosition]<mask[position])
		{
		  mask8[newPosition]=LIVER_8SEGMENT_PART9;
		  Q.push(Point3D<int>(temp.x,temp.y,temp.z-1)); 
		  flag[newPosition]=1;
		}
		
		newPosition=position+iDim[0];
		if(temp.y<iDim[1]-1 && flag[newPosition]==0 && mask8[newPosition]!=blank && mask[newPosition]<mask[position])
		{
		  mask8[newPosition]=LIVER_8SEGMENT_PART9;
		  Q.push(Point3D<int>(temp.x,temp.y+1,temp.z));
		  flag[newPosition]=1;
		}
		
		newPosition=position-iDim[0];
		if(temp.y>0 && flag[newPosition]==0 && mask8[newPosition]!=blank && mask[newPosition]<mask[position]) 
		{
		  mask8[newPosition]=LIVER_8SEGMENT_PART9;
		  Q.push(Point3D<int>(temp.x,temp.y-1,temp.z)); 
		  flag[newPosition]=1;
		}
		
		newPosition=position+1;
		if(temp.x<iDim[0]-1 && flag[newPosition]==0 && mask8[newPosition]!=blank && mask[newPosition]<mask[position]) 
		{
		  mask8[newPosition]=LIVER_8SEGMENT_PART9;
		  Q.push(Point3D<int>(temp.x+1,temp.y,temp.z));
		  flag[newPosition]=1;
		}
		
		newPosition=position-1;
		if(temp.x>0 && flag[newPosition]==0 && mask8[newPosition]!=blank && mask[newPosition]<mask[position]) 
        {
		  mask8[newPosition]=LIVER_8SEGMENT_PART9;
		  Q.push(Point3D<int>(temp.x-1,temp.y,temp.z)); 
		  flag[newPosition]=1;
		}

		//新增加12 下一层
		newPosition=position+pageSize+iDim[0];
		if(temp.z<iDim[2]-1 && temp.y<iDim[1]-1 && flag[newPosition]==0 && mask8[newPosition]!=blank && mask[newPosition]<mask[position])
	    {
		  mask8[newPosition]=LIVER_8SEGMENT_PART9;
		  Q.push(Point3D<int>(temp.x,temp.y+1,temp.z+1)); 
		  flag[newPosition]=1;
		}

		newPosition=position+pageSize-iDim[0];
		if(temp.z<iDim[2]-1 && temp.y>0 && flag[newPosition]==0 && mask8[newPosition]!=blank && mask[newPosition]<mask[position]) 
		{
		   mask8[newPosition]=LIVER_8SEGMENT_PART9;
		  Q.push(Point3D<int>(temp.x,temp.y-1,temp.z+1));
		  flag[newPosition]=1;
		}
		
		newPosition=position+pageSize+1;
		if(temp.z<iDim[2]-1 && temp.x<iDim[0]-1 && flag[newPosition]==0 && mask8[newPosition]!=blank && mask[newPosition]<mask[position]) 
		{
		   mask8[newPosition]=LIVER_8SEGMENT_PART9;
		  Q.push(Point3D<int>(temp.x+1,temp.y,temp.z+1)); 
		  flag[newPosition]=1;
		}
		
		newPosition=position+pageSize-1;
		if(temp.z<iDim[2]-1 && temp.x>0 && flag[newPosition]==0 && mask8[newPosition]!=blank && mask[newPosition]<mask[position]) 
		{
		   mask8[newPosition]=LIVER_8SEGMENT_PART9;
		   Q.push(Point3D<int>(temp.x-1,temp.y,temp.z+1)); 
		   flag[newPosition]=1;
		}
		//上一层
		newPosition=position-pageSize+iDim[0];
		if(temp.z>0 && temp.y<iDim[1]-1 && flag[newPosition]==0 && mask8[newPosition]!=blank && mask[newPosition]<mask[position])
		{
		   mask8[newPosition]=LIVER_8SEGMENT_PART9;
		   Q.push(Point3D<int>(temp.x,temp.y+1,temp.z-1)); 
		   flag[newPosition]=1;
		}
		
		newPosition=position-pageSize-iDim[0];
		if(temp.z>0 && temp.y>0 && flag[newPosition]==0 && mask8[newPosition]!=blank && mask[newPosition]<mask[position])
		{
		   mask8[newPosition]=LIVER_8SEGMENT_PART9;
		   Q.push(Point3D<int>(temp.x,temp.y-1,temp.z-1)); 
		   flag[newPosition]=1;
		}
		
		newPosition=position-pageSize+1;
		if(temp.z>0 && temp.x<iDim[0]-1 && flag[newPosition]==0 && mask8[newPosition]!=blank && mask[newPosition]<mask[position]) 
		{
		   mask8[newPosition]=LIVER_8SEGMENT_PART9;
		   Q.push(Point3D<int>(temp.x+1,temp.y,temp.z-1));
		   flag[newPosition]=1;
		}
		
		newPosition=position-pageSize-1;
		if(temp.z>0 && temp.x>0 && flag[newPosition]==0 && mask8[newPosition]!=blank && mask[newPosition]<mask[position]) 
		{
		   mask8[newPosition]=LIVER_8SEGMENT_PART9;
		   Q.push(Point3D<int>(temp.x-1,temp.y,temp.z-1));
		   flag[newPosition]=1;
		}

		//本层
		newPosition=position+iDim[0]+1;
		if(temp.x<iDim[0]-1 && temp.y<iDim[1]-1 && flag[newPosition]==0 && mask8[newPosition]!=blank  && mask[newPosition]<mask[position]) 
		{
		   mask8[newPosition]=LIVER_8SEGMENT_PART9;
		   Q.push(Point3D<int>(temp.x+1,temp.y+1,temp.z));
		   flag[newPosition]=1;
		}
		
		newPosition=position-iDim[0]+1;
		if(temp.x<iDim[0]-1 && temp.y>0 && flag[newPosition]==0 && mask8[newPosition]!=blank && mask[newPosition]<mask[position]) 
		{
		   mask8[newPosition]=LIVER_8SEGMENT_PART9;
		   Q.push(Point3D<int>(temp.x+1,temp.y-1,temp.z));
		   flag[newPosition]=1;
		}
		
		newPosition=position+iDim[0]-1;
		if(temp.x>0 && temp.y<iDim[1]-1 && flag[newPosition]==0 && mask8[newPosition]!=blank && mask[newPosition]<mask[position])
		{
		   mask8[newPosition]=LIVER_8SEGMENT_PART9;
		   Q.push(Point3D<int>(temp.x-1,temp.y+1,temp.z));
		   flag[newPosition]=1;
		}
		
		newPosition=position-iDim[0]-1;
		if(temp.x>0 && temp.y>0 && flag[newPosition]==0 && mask8[newPosition]!=blank && mask[newPosition]<mask[position]) 
		{
		   mask8[newPosition]=LIVER_8SEGMENT_PART9;
		   Q.push(Point3D<int>(temp.x-1,temp.y-1,temp.z));
		   flag[newPosition]=1;
		}
		Q.pop();
	  }
	  delete[]flag;
	}

	// 栈排序函数
	void SegFunction::StackSort(stack<int>& s, int *pSrc)  
	{  
		if(s.empty() || s.size() == 1)  
			return;  
		stack<int> tmpStack;  
		int first = s.top();  
		tmpStack.push(first);  
		s.pop();  
   
		while(!s.empty())  
		{  
			int top = s.top();  // 局部变量 暂存栈顶元素
			s.pop();  
			while(!tmpStack.empty() && pSrc[top] > pSrc[tmpStack.top()])  // 当原栈中的值 大于 临时栈时，将该坐标pop回原栈中。
			{  
				int tmp1 = tmpStack.top();  
				tmpStack.pop();  
				s.push(tmp1);  
			}  
			tmpStack.push(top);   // 直到原栈中的值 小于 临时栈，将该元素进临时栈。
		}  
   
		while(!tmpStack.empty())  // 临时栈为升序，全部pop回原栈即为降序排列(从大到小，栈顶元素最大)
		{  
			int tmp2 = tmpStack.top();  
			tmpStack.pop();  
			s.push(tmp2);  
		}  
	}  

		//unsigned char改成int
	bool SegFunction::WaterShedNew(int *pSrc,//归一化到0-255 代价图
			unsigned char * SeedImage,//Marker 种子点 标签从1开始
			char * pDst,const int *iDim,char * m_pMask,int num)//输出
		{
			if (nullptr == pSrc || nullptr == SeedImage || nullptr == pDst)
				return false;

			stack<int> Seeds;
			queue<int> Seeds_temp;
			int iLength = iDim[0]*iDim[1]*iDim[2];
			int iSizeXY = iDim[0]*iDim[1];
			int maxWaterLevel=0;

			for (int i = iLength-1; i >=0; --i)
			{
				if (SeedImage[i] > 0)
				{
					Seeds.push(i);
					if(maxWaterLevel<pSrc[i]) maxWaterLevel=pSrc[i];
				}
			}
			StackSort(Seeds, pSrc);
			
			int Neighbor6[6] = {1, -1, iDim[0], -iDim[0], iSizeXY, -iSizeXY};
			int flag[6];
			
			for(int waterlevel = maxWaterLevel; waterlevel > 0; waterlevel--)  
			{
				while(!Seeds.empty())
				{
					int iSeed = Seeds.top();
					if(pSrc[iSeed] < waterlevel) break;
					
					while(!Seeds.empty() && pSrc[iSeed] >= waterlevel)
					{
						Seeds_temp.push(iSeed);
						Seeds.pop();
						if(Seeds.empty()) break;
						iSeed = Seeds.top();
					}
					while(!Seeds_temp.empty())
					{
						int iSeed = Seeds_temp.front();
						Seeds_temp.pop();

						for (int i = 0; i < 6; i++)
						{
							flag[i] = 0;
							int iNeighbor = iSeed + Neighbor6[i];
							int zz = iNeighbor / iSizeXY;
							int yy = iNeighbor % iSizeXY / iDim[0];
							int xx = iNeighbor % iDim[0];
							if (xx < 1 || xx > iDim[0]-2 || yy < 1 || yy > iDim[1]-2 || zz < 1 || zz > iDim[2]-2)
							{
								continue;
							}
							if (SeedImage[iNeighbor] == 0 && m_pMask[iNeighbor] !=0) //SeedImage[iNeighbor] == 0表示还未访问
							{
								if(pSrc[iNeighbor] >= waterlevel)
								{
									SeedImage[iNeighbor] = SeedImage[iSeed];
									Seeds_temp.push(iNeighbor);
								}
								else if(pSrc[iNeighbor] > 0)
									flag[i] = 1;  //表示此邻域点没有增长
							}
						}
						for(int i = 0; i < 6; i++)
						{
							if(flag[i] == 1) {Seeds.push(iSeed); break;}
						}

						/*if(Seeds_temp.empty() && !Seeds.empty())
						{
							int top = Seeds.top();
							while(pSrc[top] >= waterlevel)
							{
								Seeds_temp.push(top);
								Seeds.pop();
								if(Seeds.empty()) break;
								top = Seeds.top();
							}
							break;
						}*/
					}
					// 输出中间结果
					//{
					//	char ss[16]; //这个长度根据需要  
					//	sprintf(ss, "%d", waterlevel); 
					//	string temp(ss);
					//	string fileName = gFileName + "middleResult_" + temp + ".raw";
					//	writeData(SeedImage, fileName, iDim);
					//}
					break;
				}
			}
			
			//writeData(SeedImage, gFileName + "middleResult_4.raw",iDim);


			unsigned char ucNum(num); //种子点的个数
			vector<queue<int>*> vque(ucNum);
			vector<int*> SeedCounts(ucNum);
			for (unsigned char i = 0; i < ucNum; ++i)
			{
				vque[i] = new queue<int> [256]();
				SeedCounts[i] = new int[256]();
			}
			//此时seedImage已经向下流淌涨水了 对于SeedImage不为0，但是它周围有0的点入队vque[标签][距离]，并且统计个数
			for (int i = 0; i < iLength; ++i)
			{
				if (SeedImage[i] == 0 || SeedImage[i] == 127) continue;
				int zz = i / iSizeXY;
				int yy = i % iSizeXY /iDim[0];
				int xx = i % iDim[0];
				if (xx < 1 || xx > iDim[0]-2 || yy < 1 || yy > iDim[1]-2 || zz < 1 || zz > iDim[2]-2)
					continue;
				for (int j = 0; j < 6; ++j)
				{
					int iNeighbor = i + Neighbor6[j];
					if (SeedImage[iNeighbor] == 0 && m_pMask[iNeighbor] != 0)
					{
						vque[SeedImage[i]-1][pSrc[i]].push(iNeighbor);
						SeedCounts[SeedImage[i]-1][pSrc[i]]++;

						SeedImage[iNeighbor] = 127;//标记后，不再访问
						break;
					}
				}
			}

			for (int i = 0; i < iLength; ++i)
			{
				if (SeedImage[i] > 0 && SeedImage[i] != 127)
					pDst[i] = SeedImage[i];
			}

			//WriteData(SeedImage, iLength, "E:/LungLobeData/test/watershed_after.raw");

			//分水岭
			ucNum = num;
			bool actives = 0;
			for(int waterlevel = 0; waterlevel<255; waterlevel++)
			{
				actives = 1;
				while(actives)
				{
					actives = 0;
					for(unsigned char i = 0; i<ucNum; i++)                             //对每个连通域
					{
						if(vque[i][waterlevel].empty())
							continue;

						actives = 1;
						while(SeedCounts[i][waterlevel]>0)
						{
							SeedCounts[i][waterlevel]--;
							int temp = vque[i][waterlevel].front();
							vque[i][waterlevel].pop();
							int zz = temp / iSizeXY;
							int yy = temp % iSizeXY / iDim[0];
							int xx = temp % iDim[0];
							if (xx < 1 || xx > iDim[0]-2 || yy < 1 || yy > iDim[1]-2 || zz < 1 || zz > iDim[2]-2)
								continue;

							for(int k = 0; k<6; k++)
							{
								int idxn = temp + Neighbor6[k];    // idxn——六邻域坐标位置

								if(pDst[idxn] != 0 || pSrc[idxn] <= 0 || m_pMask[idxn] ==0  ) // 1.判断是否有标签  2.距离是否大于0  3.是否为肝(m_pMask!=0为肝)
									continue;

								pDst[idxn] = i+1;  //pDst 输出赋值  赋予标签
								if(pSrc[idxn]<=waterlevel) 
								{
									vque[i][waterlevel].push(idxn);  
								}
								else
								{
									vque[i][pSrc[idxn]].push(idxn);
									SeedCounts[i][pSrc[idxn]]++;
								}		
							}
						}
						SeedCounts[i][waterlevel] = static_cast<int>(vque[i][waterlevel].size());

					}

				}
 				/*if (waterlevel % 10 == 0)
 					WriteData(pDst, iLength, "E:/LungLobeData/test/watershed_after.raw");*/
			}

			//writeData(pDst,"F:\\CentreLine2\\1213-5\\WangChaofeng\\waterShed_imoprove.raw",iDim);

			for (int i = 0; i < iLength; ++i)
			{
				if (m_pMask[i] ==0)
					pDst[i] = 0;
				if (SeedImage[i] == 127)
					SeedImage[i] = 0;
			}

			while(!vque.empty())
			{
				delete[] vque.back();
				vque.pop_back();
			}
			while(!SeedCounts.empty())
			{
				delete[] SeedCounts.back();
				SeedCounts.pop_back();
			}

			return true;
		}
	////unsigned char改成int
	//bool SegFunction::WaterShedNew(int *pSrc,//归一化到0-255 代价图
	//		unsigned char * SeedImage,//Marker 种子点 标签从1开始
	//		char * pDst,const int *iDim,char * m_pMask,int num)//输出
	//	{
	//		if (nullptr == pSrc || nullptr == SeedImage || nullptr == pDst)
	//			return false;

	//		stack<int> Seeds;
	//		unsigned char ucNum(num);         // 种子点的个数
	//		vector<queue<int>> Seeds_temp(ucNum);
	//		
	//		int iLength = iDim[0]*iDim[1]*iDim[2];
	//		int iSizeXY = iDim[0]*iDim[1];
	//		int maxWaterLevel=0;

	//		for (int i = 0; i < iLength; i++)
	//		{
	//			if (SeedImage[i] > 0)  // 找出标签大于0的点（种子点）
	//			{
	//				Seeds.push(i);
	//				if(pSrc[i] > maxWaterLevel)
	//				{
	//					maxWaterLevel = pSrc[i];
	//				}
	//			}
	//		}
	//		StackSort(Seeds, pSrc);
	//		
	//		int Neighbor6[6] = {1, -1, iDim[0], -iDim[0], iSizeXY, -iSizeXY};
	//		int flag[6];
	//		bool seeds_tempEmpty = true;   // 标记vector Seeds_temp队列是否为空
	//		for(int waterlevel = maxWaterLevel; waterlevel > 0; waterlevel--)  
	//		{
	//			while(!Seeds.empty())
	//			{
	//				int iSeed = Seeds.top();
	//				if(pSrc[iSeed] < waterlevel) break;
	//				
	//				while(pSrc[iSeed] >= waterlevel)
	//				{
	//					Seeds_temp[SeedImage[iSeed] - 1].push(iSeed); //vector下标从0开始，标签下标从1开始
	//					seeds_tempEmpty = false;
	//					Seeds.pop();
	//					if(Seeds.empty()) break;
	//					iSeed = Seeds.top();
	//				}

	//				while(!seeds_tempEmpty)
	//				{
	//					int seeds_tempEmpty_Num = 0; // 统计Seeds_temp队列为空的个数
	//					for(int seedsTempIndex = 0; seedsTempIndex < ucNum; seedsTempIndex++) // 循环遍历所有队列
	//					{
	//						if(!Seeds_temp[seedsTempIndex].empty())
	//						{
	//							int iSeeds_temp = Seeds_temp[seedsTempIndex].front();
	//							Seeds_temp[seedsTempIndex].pop();

	//							int zz = iSeeds_temp / iSizeXY;
	//							int yy = iSeeds_temp % iSizeXY / iDim[0];
	//							int xx = iSeeds_temp % iDim[0];
	//							if (xx < 1 || xx > iDim[0]-2 || yy < 1 || yy > iDim[1]-2 || zz < 1 || zz > iDim[2]-2)
	//							{
	//								continue;
	//							}

	//							for (int i = 0; i < 6; i++)
	//							{
	//								flag[i] = 0;

	//								int iNeighbor = iSeeds_temp + Neighbor6[i];

	//								if (SeedImage[iNeighbor] == 0 && m_pMask[iNeighbor] !=0) //SeedImage[iNeighbor] == 0表示还未访问
	//								{
	//									if(pSrc[iNeighbor] >= waterlevel)
	//									{
	//										SeedImage[iNeighbor] = SeedImage[iSeeds_temp];  // 设置邻域的标签与当前种子点的标签相同
	//										Seeds_temp[seedsTempIndex].push(iNeighbor);
	//									}
	//									else if(pSrc[iNeighbor] > 0)
	//										flag[i] = 1;  //表示此邻域点没有增长完
	//								}
	//							}
	//							for(int i = 0; i < 6; i++)
	//							{
	//								if(flag[i] == 1) {Seeds.push(iSeeds_temp); break;}
	//							}
	//						}
	//						else 
	//						{
	//							seeds_tempEmpty_Num ++;   // 若队列为空，则计数加1
	//						}
	//					}
	//					if(ucNum == seeds_tempEmpty_Num) 
	//					{
	//						seeds_tempEmpty = true; // 所有队列均为空，设置标记为true
	//					}
	//				}
	//				 //输出中间结果
	//				{
	//					char ss[16]; //这个长度根据需要  
	//					sprintf(ss, "%d", waterlevel); 
	//					string temp(ss);
	//					string fileName = gFileName + "middleResult_" + temp + ".raw";
	//					writeData(SeedImage, fileName, iDim);
	//				}
	//				break;  // 当所有队列均为空时，降水深
	//			}
	//		}
	//		
	//		//writeData(SeedImage, gFileName + "middleResult_4.raw",iDim);
	//		for (int i = 0; i < iLength; i++)
	//		{
	//			if (SeedImage[i] > 0)
	//			{
	//				pDst[i] = SeedImage[i];
	//			}
	//			else if (m_pMask[i] ==0)
	//			{
	//				pDst[i] = 0;
	//			}
	//		}
	//		return true;
	//	}


 //根据手工选取的三个点分割尾叶
void SegFunction::seg_CaudateLobe(const int* pointa,const int *pointb,const int *pointc,char *pMask,const int *iDim)
{
	int len=iDim[0]*iDim[1]*iDim[2];
	/*int size[3];
	size[0]=iDim[0];
	size[1]=iDim[1];
	size[2]=iDim[2];*/
	char *mask=new char[len];
	memcpy(mask,pMask,len*sizeof(char));
	int plane[4];
	generate_plane_3point(pointa,pointb,pointc,plane);
	printf("1: plane %dx+ %dy+ %dz+ %d =0\n",plane[0],plane[1],plane[2],plane[3]);
	int m=0;
	int num1=0;
	int num2=0;
	for(int i=0;i<iDim[2];i++)
	{
		for(int j=0;j<iDim[1];j++)
		{
			for(int k=0;k<iDim[0];k++)
			{
				m=i*iDim[0]*iDim[1]+j*iDim[0]+k;
				if(mask[m]==LIVER_8SEGMENT_PART2 || mask[m]==LIVER_8SEGMENT_PART3)
				{
					int ans=k*plane[0]+j*plane[1]+i*plane[2]+plane[3];//ans=Ax+By+Cz+D;
					if(ans>0)
					{
						mask[m]=TEMPMARK1;
						num1++;
					}
					else
					{
						mask[m]=TEMPMARK2;
						num2++;
					}
				}
				/*else
				{
					pMask[m]=0;
				}*/
			}
		}
	}
	// 区域增长
	    //writeData(mask,"F:\\CentreLine2\\1213-5\\HuangGuanglan\\test1.raw",iDim);
	    int tempmask;
		if(num1<num2)  tempmask=TEMPMARK1;
		else tempmask=TEMPMARK2;
		int min=0;
		int dis=0;
		int point[3];
		int minpoint[3]={0};
	    for(int i=0;i<iDim[2];i++)
	   {
		for(int j=0;j<iDim[1];j++)
		 {
			for(int k=0;k<iDim[0];k++)
			{
				m=i*iDim[0]*iDim[1]+j*iDim[0]+k;
				if(mask[m]-tempmask==0)
				{
					point[0]=k;
					point[1]=j;
					point[2]=i;
					dis=pointToLine(point,veinPoint,portalPoint);
					if(min==0) 
					{
					  min=dis;
					  minpoint[0]=k;
					  minpoint[1]=j;
					  minpoint[2]=i;
					}
					else if(dis<min)
					{
					  min=dis;
					  minpoint[0]=k;
					  minpoint[1]=j;
					  minpoint[2]=i;
					}
				}
			}
		}
		}
      //根据找到的点进行区域增长
		region_grow(minpoint,mask,iDim);

		//writeData(mask,"F:\\CentreLine2\\1213-5\\HuangGuanglan\\test2.raw",iDim);
		for(int i=0;i<iDim[2];i++)
	   {
		for(int j=0;j<iDim[1];j++)
		 {
			for(int k=0;k<iDim[0];k++)
			{
				m=i*iDim[0]*iDim[1]+j*iDim[0]+k;
				if(mask[m]!=OTHERS)
					pMask[m]=LIVER_8SEGMENT_PART9;
			}
		}
		}
		delete[]mask;
}


 void SegFunction::seg_CaudateLobe2(const int* point2a,const int *point2b,const int *point2c,int &portalLineR,char *pMask,const int *iDim)
 {
	    int len=iDim[0]*iDim[1]*iDim[2];
		int plane[4];
		generate_plane_3point(point2a,point2b,point2c,plane);
		printf("1: plane %dx+ %dy+ %dz+ %d =0\n",plane[0],plane[1],plane[2],plane[3]);

	    int m;
		for(int i=0;i<iDim[2];i++)
		  {
			for(int j=0;j<iDim[1];j++)
			{
				for(int k=0;k<iDim[0];k++)
				{
					m=i*iDim[0]*iDim[1]+j*iDim[0]+k;
					if(pMask[m]==LIVER_8SEGMENT_PART9)
					{
						int ans=k*plane[0]+j*plane[1]+i*plane[2]+plane[3];//ans=Ax+By+Cz+D;
						if(ans<0)
						{
							pMask[m]=LIVER_8SEGMENT_PART7;
						}
					}
				}
			}
		}
       seg_mask_8_3(portalLineR,pMask,iDim);
 }

 void SegFunction::Minivalue(char *pMask,float *data,const int *iDim)
 {
	//short 
	 int length=iDim[0]*iDim[1]*iDim[2];
	 int area=iDim[0]*iDim[1];
	 int pos_x1=0;
	 int pos_x2=0;
	 int pos_x3=0;
	 int pos_y1=0;
	 int pos_y2=0;
	 int pos_y3=0;
	 int Ng;
	 float *result=new float[length];
	 Ng=static_cast<int>(ceil(fNgParm*std_Gb))+1;
	 std_Gb=5*fStdGbParm/fNorm;
	 //Gaussian_3D(result,Ng,std_Gb,data);
	 queue<Point3D<int>> Q;
   for(int i=1;i<iDim[0]-1;i++)
	   for(int j=1;j<iDim[1]-1;j++)
		   for(int k=1;k<iDim[2]-1;k++)
		   {
			   int pos=k*area+j*iDim[0]+i;
			   if((pMask[pos]==LIVER_8SEGMENT_PART2 || pMask[pos]==LIVER_8SEGMENT_PART3) && minPoint(result,i,j,k,iDim))
			 {
				 Q.push(Point3D<int>(i,j,k)); 
				//  pos_x1=pos-1;  //x-1
				//  pos_x2=pos;   //x
				//  pos_x3=pos+1;   //x+1
			 // 
				//  pos_y1=pos-iDim[0]; //y-1
				//  pos_y2=pos;   //y
				//  pos_y3=pos+iDim[0];   //y+1

				//  if(data[pos_x2]-data[pos_x1]>0 && data[pos_x2]-data[pos_x1]<2 && data[pos_y2]-data[pos_y1]>0 && data[pos_y2]-data[pos_y1]<2)
				//  {
				//	 float secDer_x=data[pos_x3]-2*data[pos_x2]+data[pos_x1];
				//	 float secDer_y=data[pos_y3]-2*data[pos_y2]+data[pos_y1];
				//	 float secDer_xy=data[pos_y3+1]-data[pos_y2+1]-data[pos_y3]+data[pos_y2];
				//	 if(secDer_x>0 && secDer_x*secDer_y-secDer_xy*secDer_xy>0)
				//	 {
    //                   float dis=(i-portalPoint[0])*(i-portalPoint[0])+(j-portalPoint[1])*(j-portalPoint[1])+(k-portalPoint[2])*(k-portalPoint[2]);
				//	   //if(dis<400)
				//	   //{
				//         Q.push(Point3D<int>(i,j,k)); 
				//	  // }
				//	 }
				//  }
			  }
		   }
		   delete[]result;
 }

	 void SegFunction::rotate(char *pMask,const int *iDimension,const int *veinPoint,const int *portalPoint,const int *portalL)
	 {
		int tempNum=iDimension[0]*iDimension[1]*iDimension[2];
		int plane[4];
		float *disData=new float[tempNum];
		memset(disData,0,tempNum*sizeof(float));
		generate_plane_3point(veinPoint,portalPoint,portalL,plane); //Ax+By+Cz+D=0
		if(plane[0]>0)
		{
			plane[0]=-plane[0]; //A
			plane[1]=-plane[1]; //B
			plane[2]=-plane[2]; //C
			plane[3]=-plane[3]; //D
		}

		float line[3]; //平面plane与水平面的交线的方向向量(line[0],line[1],line[2])
		float model=sqrt(float(plane[0]*plane[0]+plane[1]*plane[1]));
		line[0]=(-plane[1])/model;
		line[1]=(plane[0])/model;
		line[2]=0;

		float cos=plane[2]/sqrt(float(plane[0]*plane[0]+plane[1]*plane[1]+plane[2]*plane[2]));
		float sin=sqrt(1-cos*cos);

		int area=iDimension[0]*iDimension[1];
		
		float *projection=new float[area]; //构造一个水平面
		memset(projection,0,sizeof(float)*area);
		char *mask2D=new char[area];
		memset(mask2D,0,sizeof(char)*area);
		char *newdata=new char[tempNum];
		memset(newdata,0,sizeof(char)*tempNum);
		float test=0.0;

		//将门脉旋转到水平面，则旋转后的平面为 z=protal_z
		int protal_x=cos*portalPoint[0]+(1-cos)*(portalPoint[0]*line[0]+portalPoint[1]*line[1])*line[0]+sin*(-portalPoint[2])*line[1];
		int protal_y=cos*portalPoint[1]+(1-cos)*(portalPoint[0]*line[0]+portalPoint[1]*line[1])*line[1]+sin*portalPoint[2]*line[0]+iDimension[1]/2; 
		int protal_z=iDimension[2]-(cos*portalPoint[2]+sin*(portalPoint[0]*line[1]-portalPoint[1]*line[0]));

		//将整个2、3部分旋转到水平面
		for(int i=0;i<iDimension[0];i++)
			for(int j=0;j<iDimension[1];j++)  // V(i,j,k) K(line[0],line[1],0)
				for(int k=0;k<iDimension[2];k++)
				{
					int pos=k*area+j*iDimension[0]+i;
					if((pMask[pos]==LIVER_8SEGMENT_PART2 || pMask[pos]==LIVER_8SEGMENT_PART3)) //标签为2、3的表面的点才用旋转并投影到水平面  && roundValue(pMask,pos,blank,iDimension)
					{
					  float dotproduct=i*line[0]+j*line[1];
					  int x=cos*i+(1-cos)*dotproduct*line[0]+sin*(-k)*line[1];
					  int y=cos*j+(1-cos)*dotproduct*line[1]+sin*k*line[0]+iDimension[1]/2; //+256 表示向y轴平移256个单位
					  int z=iDimension[2]-(cos*k+sin*(i*line[1]-j*line[0]));
					 /* if(x>0)
					  {
					    cout<<"122341";
					  }
					  if(x<0)
					  {
					    cout<<"122341";
					  }
					  if(y<0)
					  {
					    cout<<"122341";
					  }
					  if(y>0)
					  {
					    cout<<"122341";
					  }
					  if(z<0)
					  {
					    cout<<"122341";
					  }
					  if(z>0)
					  {
					    cout<<"122341";
					  }*/
					  /*if(x<0 || x>=512 || y<0 || y>=512)
					  {
					    int t=0;
					  }*/
					  test=abs(plane[0]*i+plane[1]*j+plane[2]*k+plane[3])/sqrt(float(plane[0]*plane[0]+plane[1]*plane[1]+plane[2]*plane[2]));
					  projection[y*iDimension[0]+x]=test;
					  mask2D[y*iDimension[0]+x]=1;
					  newdata[z*area+y*iDimension[0]+x]=1;
					}
				}

              //**************************************以平面为基准向上作垂线取点
			   //for(int j=0;j<iDimension[1];j++)
				  // for(int i=0;i<iDimension[0];i++)
				  // {
				  //   int pos=protal_z*area+j*iDimension[0]+i;
					 //if(newdata[pos]==1) //即表示在平面 z=protal_z上
					 //{
					 //   mask2D[j*iDimension[0]+i]=1;
						//for(int k=iDimension[2]-1;k>=protal_z;k--)
						//{
						//  if(newdata[k*area+j*iDimension[0]+i]==1)
						//  {
						//	  projection[j*iDimension[0]+i]=k-protal_z;
						//	  break;
						//  }
						//}
					 //}
				  // }
            //***********************************************


              //writeData(newdata,"F:\\CentreLine2\\1213-5\\WangChaofeng\\newdata1.raw",iDimension);


			  ////旋转后平面的z轴值为pos_z
			  //int pos_z=0;
			  //pos_z=iDimension[2]-(cos*portalPoint[2]+sin*(portalPoint[0]*line[1]-portalPoint[1]*line[0]));
			  //int pointOnPlane=pos_z*area;
			  //for(int j=0;j<iDimension[1];j++)
				 // for(int i=0;i<iDimension[0];i++)
				 // {
				 //   int pOP=pointOnPlane+j*iDimension[0]+i;
					////if(newdata[pOP]!=0)
				 // }
			//saveBmp("oriseed3.bmp",projection,iDimension[0],iDimension[1],8);
				//
         
	     //对二维图片进行高斯平滑  
			  int ksize=7;
			  float gama=3;
			  float *s_projection=new float[area];
			  memset(s_projection,0.0,sizeof(float)*area);
         Gaussian_2D(s_projection,iDimension[0],iDimension[1],ksize,gama,projection); //s_projection为高斯平滑后的矩阵

         //求取二维图片的极大值作为分水岭的种子点
		vector<int> seedpoints;
		vector<double> tempDistace;
		queue<Point3D<int>> Q;
		int searchResult[2];
		int tempPos=0;
		int num=0;
		double mindis=0.0;
		int seed_pos=0;
		unsigned char * SeedImage=new unsigned char[area];
		memset(SeedImage,0,sizeof(unsigned char)*area);
		 for(int j=0;j<iDimension[1];j++)
			 for(int k=0;k<iDimension[0];k++)
	           {
	             if((s_projection[tempPos]>0) && maxPoint(s_projection,k,j,iDimension)) //如果它是极大值点
				 {
                   searchResult[0]=k;
				   searchResult[1]=j;
				   //double tempdis=pointToPoint(searchResult,portalPoint);
				   //double tempdis=pointToLine(searchResult,veinPoint,veinPoint);
				   double tempdis=(k-protal_x)*(k-protal_x)+(j-protal_y)*(j-protal_y);
				   if(mindis<0.01) mindis=tempdis;
				   else if(tempdis<mindis) 
				   {
					   mindis=tempdis;
					   seed_pos=tempPos;
				   }
				   num++;
				   SeedImage[tempPos]=num;
				   Q.push(Point3D<int>(searchResult[0],searchResult[1],0));
				   //tempDistace.push_back(tempdis);
				  
				 }
				 tempPos++;
	           }

		   //对二维图片进行分水岭算法
			 char *pDst=new char[area];
			 memset(pDst,0,sizeof(char)*area);
			 unsigned char *pSrc=new unsigned char[area];
			 for(int i=0;i<area;i++)
			 {
			   if(s_projection[i]<1 && s_projection[i]>0.05)
				 pSrc[i]=s_projection[i]+1;
			   else pSrc[i]=s_projection[i];
			 }
			 WaterShed2D(pSrc,SeedImage,pDst,mask2D,iDimension,num);

			//z=288
			 int planepos=288*area;
			 for(int j=0;j<iDimension[1];j++)
				 for(int i=0;i<iDimension[0];i++)
				 {
				   int pos=j*iDimension[1]+i;
				   if(pDst[pos]==pDst[seed_pos]) //标记种子点所在的块
					   newdata[planepos+pos]=LIVER_8SEGMENT_PART9;
				   else newdata[planepos+pos]=pDst[pos];
				 }
           //writeData(newdata,"F:\\CentreLine2\\1213-5\\WangChaofeng\\water2d_plane.raw",iDimension);

		   //在分出来的块中选出尾叶和其他部分的两个交界点，并将点旋转回原来位置获取坐标  尾叶 标签为LIVER_8SEGMENT_PART9 9


            delete[]mask2D; 
		    delete[]pSrc;
			delete[]s_projection;
			delete[]projection;
			delete[]newdata;
			delete[]SeedImage;
			delete[]pDst;
	 }

	 bool SegFunction::maxPoint(float *newdata,int x,int y,const int *iDim) //平面上寻找极大值点
	 {
	      int len=iDim[0]*iDim[1];
		  int newX;
		  int newY;
		  int position=y*iDim[0]+x;
		  int newPosition;

	    newPosition=position+1;
		if(x==iDim[0]-1 || (newPosition<len && newdata[newPosition]>=newdata[position])) return false;

		newPosition=position-1;	 
		if(x==0 || (newPosition<len && newdata[newPosition]>=newdata[position])) return false;

		newPosition=position+iDim[0];
		if(y==iDim[0]-1 || (newPosition<len && newdata[newPosition]>=newdata[position])) return false;

		newPosition=position-iDim[0];	 
		if(y==0 || (newPosition<len && newdata[newPosition]>=newdata[position])) return false;

		return true;
	 }

	 //pSrc归一化到0-255 代价图      SeedImage种子点 标签从1开始      pDst输出  num种子点个数
	 bool SegFunction::WaterShed2D(unsigned char *pSrc,unsigned char * SeedImage,char * pDst,char *mask2D,const int *iDim,int num)//输出
		{
			if (nullptr == pSrc || nullptr == SeedImage || nullptr == pDst)
				return false;

			queue<int> Seeds;
			int iLength = iDim[0]*iDim[1];
			//int iSize[3] = { m_pImage->SizeX(), m_pImage->SizeY(), m_pImage->SizeZ() };
			//int iSizeX = m_pImage->SizeX();
			//int iSizeXY = iDim[0]*iDim[1];
			for (int i = 0; i < iLength; ++i)
			{
				if (SeedImage[i] > 0)
					Seeds.push(i);
			}

			//WriteData(SeedImage, iLength, "E:/LungLobeData/test/watershed_before.raw");

			//向下流淌
			int Neighbor4[4] = {1, -1, iDim[0], -iDim[0]};
			while(!Seeds.empty())
			{
				int iSeed = Seeds.front();
				Seeds.pop();
				int yy = iSeed / iDim[0];
				int xx = iSeed % iDim[0];
				if (xx < 1 || xx > iDim[0]-2 || yy < 1 || yy > iDim[1]-2 )
					continue;

				for (int i = 0; i < 4; ++i)
				{
					int iNeighbor = iSeed + Neighbor4[i];
					if (SeedImage[iNeighbor] == 0 && pSrc[iNeighbor] <= pSrc[iSeed] && mask2D[iNeighbor] !=0)
					{
						SeedImage[iNeighbor] = SeedImage[iSeed]; //将种子点的标签赋给它周围代价比它低的点
						Seeds.push(iNeighbor);
					}
				}
			}

			//WriteData(SeedImage, iLength, "E:/LungLobeData/test/watershed_before.raw");

			unsigned char ucNum(num); //种子点的个数
			vector<queue<int>*> vque(ucNum);
			vector<int*> SeedCounts(ucNum);
			for (unsigned char i = 0; i < ucNum; ++i)
			{
				vque[i] = new queue<int> [256]();
				SeedCounts[i] = new int[256]();
			}
			for (int i = 0; i < iLength; ++i)
			{
				if (SeedImage[i] == 0 || SeedImage[i] == 127) continue;
				//int zz = i / iSizeXY;
				int yy = i /iDim[0];
				int xx = i % iDim[0];
				if (xx < 1 || xx > iDim[0]-2 || yy < 1 || yy > iDim[1]-2 )
					continue;
				for (int j = 0; j < 4; ++j)
				{
					int iNeighbor = i + Neighbor4[j];
					if (SeedImage[iNeighbor] == 0 && mask2D[iNeighbor] != 0)
					{
						vque[SeedImage[i]-1][pSrc[i]].push(iNeighbor); //vque[种子点的标签][代价] 中存点的位置
						SeedCounts[SeedImage[i]-1][pSrc[i]]++;

						SeedImage[iNeighbor] = 127; //标记此点已访问
						break;
					}
				}
			}

			for (int i = 0; i < iLength; ++i)
			{
				if (SeedImage[i] > 0 && SeedImage[i] != 127)
					pDst[i] = SeedImage[i];
			}

			//WriteData(SeedImage, iLength, "E:/LungLobeData/test/watershed_after.raw");

			//分水岭
			ucNum = num;
			bool actives = 0;
			for(int waterlevel = 0; waterlevel<255; waterlevel++)       
			{
				actives = 1;
				while(actives)
				{
					actives = 0;
					for(unsigned char i = 0; i<ucNum; i++)                             //对每个连通域
					{
						if(vque[i][waterlevel].empty())
							continue;

						actives = 1;
						while(SeedCounts[i][waterlevel]>0)
						{
							SeedCounts[i][waterlevel]--;
							int temp = vque[i][waterlevel].front();
							vque[i][waterlevel].pop();
							//int zz = temp / iSizeXY;
							int yy = temp  / iDim[0];
							int xx = temp % iDim[0];
							if (xx < 1 || xx > iDim[0]-2 || yy < 1 || yy > iDim[1]-2)
								continue;

							for(int k = 0; k<4; k++)
							{
								int idxn = temp + Neighbor4[k];

								if(pDst[idxn] != 0 || pSrc[idxn] <= 0 )
									continue;

								pDst[idxn] = i+1; //赋予标签
								if(pSrc[idxn]<=waterlevel)
								{
									vque[i][waterlevel].push(idxn);
								}
								else
								{
									vque[i][pSrc[idxn]].push(idxn);
									SeedCounts[i][pSrc[idxn]]++;
								}		
							}

						}
						SeedCounts[i][waterlevel] = static_cast<int>(vque[i][waterlevel].size());

					}

				}
 				/*if (waterlevel % 10 == 0)
 					WriteData(pDst, iLength, "E:/LungLobeData/test/watershed_after.raw");*/
			}

			//writeData(pDst,"F:\\CentreLine2\\1213-5\\WangChaofeng\\waterShed111.raw",iDim);

			for (int i = 0; i < iLength; ++i)
			{
				if (pSrc[i] ==0)
					pDst[i] = 0;
				if (SeedImage[i] == 127)
					SeedImage[i] = 0;
			}

			while(!vque.empty())
			{
				delete[] vque.back();
				vque.pop_back();
			}
			while(!SeedCounts.empty())
			{
				delete[] SeedCounts.back();
				SeedCounts.pop_back();
			}

			return true;
		}


		
		 //bool LungLobe::WaterShed3D(unsigned char *pSrc,//归一化到0-255
			//unsigned char * SeedImage,//Marker
			//unsigned char * pDst)// 输出
  //       bool SegFunction::WaterShedNew(unsigned char *pSrc,//归一化到0-255 代价图
		//	unsigned char * SeedImage,//Marker 种子点 标签从1开始
		//	char * pDst,const int *iDim,char * m_pMask,int num)//输出
		//{
		//	if(nullptr == pSrc || nullptr == SeedImage || nullptr == pDst)
		//		return false;

		//	int iDimension[3] = { iDim[0],iDim[1],iDim[2]};
		//	int iSliceNum = iDimension[0]*iDimension[1];
		//	int iVolumeNum = iSliceNum*iDimension[2];

		//	unsigned char ucNum = num; // label number
		//	unsigned char ucExist[20] = {0};
		//	vector<int*> SeedCounts(num);//维度:第一维:label number;第二维:灰度阶(0-255),保存每个区域的种子点集的个数,种子点集的个数以灰度值划分为属于0-255不同灰度阶的种子点的个数.
		//	queue<Vector3D_i> quetem;//根据Marker寻找种子点集时,用到的临时保存队列,保存区域增长的结果
		//	//保存所有标记区域种子队列的数组，里面放的是种子队列的指针
		//	vector<queue<Vector3D_i>*> vque(num);//维度:第一维:label number;第二维:灰度阶;保存每个区域的种子点集,这些种子点集以灰度阶分类进不同的队列.队列里保存了同一区域同一灰度阶的所有种子点

		//	int * GreArray;
		//	queue<Vector3D_i> *pque;

		//	int Neighbor26[26][3] = {{-1,-1,-1},{-1,-1,0},{-1,-1,1},{-1,0,-1},{-1,0,0},{-1,0,1},{-1,1,-1},{-1,1,0},{-1,1,1},{0,-1,-1},{0,-1,0},{0,-1,1},{0,0,-1},{0,0,1},{0,1,-1},{0,1,0},{0,1,1},{1,-1,-1},{1,-1,0},
		//	{1,-1,1},{1,0,-1},{1,0,0},{1,0,1},{1,1,-1},{1,1,0},{1,1,1}};
		//	int Neighbor6[6][3] = {{-1,0,0},{1,0,0},{0,-1,0},{0,1,0},{0,0,-1},{0,0,1}};
		//	memset(pDst,0,sizeof(unsigned char)*iVolumeNum);  //初始化
		//	//Mcsf::Array1D<unsigned char>bounda(iVolumeNum);

		//	bool Neighbor26Flag[26] = {0};
		//	//预处理,提取区分每个标记区域，并初始化每个标记的种子队列
		//	//种子是指标记区域边缘的点，他们可以在水位上升时向外淹没（或者说生长）
		//	//pan's words：我的理解是梯度值较小的象素点，或者是极小灰度值的点。
		//
		//	for(int z = 0; z<iDimension[2]; z++)//slice
		//	{
		//		for(int i = 0; i<iDimension[1]; i++)//row
		//		{
		//			for(int j = 0; j<iDimension[0]; j++)//col
		//			{	
		//				int idx = z*iSliceNum+i*iDimension[0]+j;
		//				if(SeedImage[idx] < 1 || SeedImage[idx] >num /*&& pSrc[idx]>0*/)
		//					continue;

		//				ucNum = SeedImage[idx];//标记号+1
		//				ucExist[ucNum-1] = 1;
		//				cout<<static_cast<int>(ucNum)<<endl;

		//				GreArray = new int[256];
		//				memset(GreArray,0,sizeof(int)*256);
		//				SeedCounts[ucNum-1] = GreArray;
		//				//指向种子队列的指针
		//				pque = new queue<Vector3D_i>[256];
		//				vque[ucNum-1] = pque;

		//				Vector3D_i temp;
		//				temp.z = z;
		//				temp.y = i;
		//				temp.x = j;
		//				quetem.push(temp);//当前点压入临时队列中
		//				//当前点已被标记过
		//				pDst[idx] = ucNum;
		//				SeedImage[idx] = 127;//表示已经处理过
		//				while(!quetem.empty())
		//				{
		//					memset(Neighbor26Flag,0,sizeof(bool)*26);
		//					temp = quetem.front();
		//					int zz = temp.z;
		//					int yy = temp.y;
		//					int xx = temp.x;
		//					quetem.pop();
		//					for(int k = 0; k<26; k++)
		//					{
		//						int zzn = zz + Neighbor26[k][2];
		//						int yyn = yy + Neighbor26[k][1];
		//						int xxn = xx + Neighbor26[k][0];
		//						if(zzn<0 || zzn>=iDimension[2] || xxn<0 || xxn>=iDimension[1] || yyn<0 || yyn>=iDimension[0])
		//						{
		//							continue;
		//						}
		//						int idxn = zzn*iSliceNum+yyn*iDimension[0]+xxn;
		//						if(SeedImage[idxn] == ucNum/*&& pSrc[idxn] >0*/)
		//						{
		//							temp.z = zzn;
		//							temp.y = yyn;
		//							temp.x = xxn;
		//							quetem.push(temp);
		//							pDst[idxn] = ucNum;
		//							SeedImage[idxn] = 127;
		//						}
		//						else if(SeedImage[idxn]==0 && pSrc[idxn]>0)
		//						{
		//							Neighbor26Flag[k] = 1;
		//						}
		//					}

		//					for(int k = 0; k<26; k++)
		//					{
		//						if(Neighbor26Flag[k] == 1)
		//						{
		//							temp.z = zz;
		//							temp.y = yy;
		//							temp.x = xx;
		//							int idxx = zz*iSliceNum+yy*iDimension[0]+xx;
		//							//bounda[idxx] = 1;
		//							vque[ucNum-1][pSrc[idxx]].push(temp);
		//							SeedCounts[ucNum-1][pSrc[idxx]]++;
		//							break;
		//						}
		//					}

		//				}//end while


		//			}
		//		}
		//	}
		//	writeData(pDst,"F:\\CentreLine2\\1213-5\\WangChaofeng\\before_waterShed3D.raw",iDim);
		//	ucNum = num;
		//	bool actives = 0;
		//	for(int waterlevel = 0; waterlevel<255; waterlevel++)       
		//	{
		//		actives = 1;
		//		while(actives)
		//		{
		//			actives = 0;
		//			for(unsigned char i = 0; i<ucNum; i++)                             //对每个连通域
		//			{
		//				if (ucExist[i] == 0) continue;

		//				if(vque[i][waterlevel].empty())
		//					continue;

		//				actives = 1;
		//				while(SeedCounts[i][waterlevel]>0)
		//				{
		//					SeedCounts[i][waterlevel]--;
		//					Vector3D_i temp = vque[i][waterlevel].front();
		//					vque[i][waterlevel].pop();
		//					int zz = temp.z;
		//					int yy = temp.y;
		//					int xx = temp.x;
		//					for(int k = 0; k<6; k++) //上下左右前后
		//					{
		//						int zzn = zz + Neighbor6[k][2];
		//						int yyn = yy + Neighbor6[k][1];
		//						int xxn = xx + Neighbor6[k][0];
		//						if(zzn<0 || zzn>=iDimension[2] || yyn<0 || yyn>=iDimension[1] || xxn<0 || xxn>=iDimension[0])
		//							continue;

		//						int idxn = zzn*iSliceNum+yyn*iDimension[0]+xxn;
		//						if(pDst[idxn] != 0 || pSrc[idxn] <= 0 || (m_pMask[idxn] != LIVER_8SEGMENT_PART2 && m_pMask[idxn] != LIVER_8SEGMENT_PART3) )
		//							continue;

		//						temp.x = xxn;
		//						temp.y = yyn;
		//						temp.z = zzn;
		//						pDst[idxn] = i+1;
		//						if(pSrc[idxn]<=waterlevel)
		//						{
		//							vque[i][waterlevel].push(temp);
		//						}
		//						else
		//						{
		//							vque[i][pSrc[idxn]].push(temp);
		//							SeedCounts[i][pSrc[idxn]]++;
		//						}		
		//					}

		//				}
		//				SeedCounts[i][waterlevel] = static_cast<int>(vque[i][waterlevel].size());

		//			}
		//		}

		//	}

		//	while(!vque.empty())
		//	{
		//		pque=vque.back();
		//		delete[] pque;
		//		vque.pop_back();
		//	}
		//	while(!SeedCounts.empty())
		//	{
		//		GreArray = SeedCounts.back();
		//		delete[] GreArray;
		//		SeedCounts.pop_back();
		//	}
		//	writeData(pDst,"F:\\CentreLine2\\1213-5\\WangChaofeng\\waterShed3D.raw",iDim);
		//	return true;
		//}


    void SegFunction::generate_line_2point(const int *a, const int *b, float *line)
	{
		//判断三点是否在一条直线上
		//平面直线的四个参数（y=kx+b）
		//a[0] x  a[1]y

		line[0] = (a[1] - b[1]) * 1.0 / (a[0] - b[0]); //k
		line[1] = a[1] - (line[0] * a[0]);  //b
	}
}

