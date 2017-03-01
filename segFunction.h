#ifndef _SEGFUNCTION_
#define _SEGFUNCTION_

#include <queue>
#include <stack>
#include <map>
#include "define.h"
#include "Windows.h"
#include <stdio.h>
#include  "ipps.h"
#include <time.h>
#include<ipp.h>
#include <conio.h>
#include <direct.h>
#include <math.h>
#include "Hull3D.h"
#include <string>
#include<time.h>
//#include "McsfAlgoVector3D.h"

namespace CbibSeg{

	template<class T>
	struct  Point3D
	{
		T x,y,z;
		Point3D():x(0),y(0),z(0){}
		Point3D(T _x,T _y,T _z):x(_x),y(_y),z(_z){}
		void set(T _x,T _y,T _z)
		{
			x=_x;y=_y;z=_z;
		}
		bool operator < (const Point3D<T>& p1)
		{
			return z<p1.z;
		}
		bool operator == (const Point3D<T>& p1)
		{
			return x==p1.x&&y==p1.y&&z==p1.z;
		}
		bool operator != (const Point3D<T>& p1)
		{
			return !operator == (p1);
		}
		Point3D<T>& operator += (const Point3D<T>& p1)
		{
			*this=this->operator+(p1);
			return *this;
		}
		Point3D<T> operator + (const Point3D<T>& p1)
		{
			return Point3D<T>(x+p1.x,y+p1.y,z+p1.z);
		}
		Point3D<T>& operator -= (const Point3D<T>& p1)
		{
			*this=this->operator-(p1);
			return *this;
		}
		Point3D<T> operator - (const Point3D<T>& p1)
		{
			return Point3D<T>(x-p1.x,y-p1.y,z-p1.z);
		}
		float dis(const Point3D<T>& pt) const
		{//两点间距离距离
			return sqrt((x-pt.x)*(x-pt.x)+(y-pt.y)*(y-pt.y)+(z-pt.z)*(z-pt.z));
		}
		void Offset( T _x, T _y, T _z )
		{
			x += _x; y += _y; z+= _z;
		}

	};
	template<class T>
	class Vector3D
	{
		
	public:
		T x,y,z;
		/// \brief Default constructor
		Vector3D():x(0),y(0),z(0){}

		/// \brief Construct from pointer
		Vector3D(T* p){ x = p[0]; y = p[1]; z = p[2]; }

		template<typename U>
		Vector3D(U* p){ x = static_cast<T>(p[0]); y = static_cast<T>(p[1]); z = static_cast<T>(p[2]); }

		///\brief Construct from 3 values
		Vector3D(T const _x,T const _y, T const _z){ x=_x; y=_y; z=_z; }

		///\brief Construct from 3 values of different type
		template<typename U>
		Vector3D(U const _x, U const _y, U const _z) { x = static_cast<T>(_x); y = static_cast<T>(_y); z = static_cast<T>(_z); }

		///\brief Construct from another Vector3D type
		Vector3D(const Vector3D<T>& b) { x = b.x; y = b.y; z = b.z; }

		///\brief Construct from another Vector3D of different type
		template<typename U>
		Vector3D(const Vector3D<U>& b) { x = static_cast<T>(b.x); y = static_cast<T>(b.y); z = static_cast<T>(b.z); }

		///\brief Set values
		void Set(T const _x,T const _y,T const _z){ x=_x; y=_y; z=_z; }

		///\brief Set values with different type
		template <typename U>
		void Set(U const _x, U const _y, U const _z){x = static_cast<T>(_x); y = static_cast<T>(_y); z = static_cast<T>(_z);}

		/// \brief Construct from pointer
		void Set(T* p){ x = p[0]; y = p[1]; z = p[2]; }

		template<typename U>
		void Set(U* p){ x = static_cast<T>(p[0]); y = static_cast<T>(p[1]); z = static_cast<T>(p[2]); }

		///\brief get member by index
		T& operator [] (int const index) { return (&x)[index]; }
		const T& operator [] (int const index) const { return (&x)[index]; }

		///\brief get x, y, and z, respectively
		T GetX() const { return x; }
		T GetY() const { return y; }
		T GetZ() const { return z; }

		///\brief sum of square
		T Var() const { return x*x+y*y+z*z;}

		///\brief standard square error
		double Std() const { return sqrt(static_cast<double>(x*x+y*y+z*z)); }

		///\brief sum of the 3 member
		T Sum() const { return x+y+z;}

		///\brief normalize the vector
		Vector3D<double> Norm() const { Vector3D<double> a; double b = Std();a.x = x / b; a.y = y / b; a.z = z / b; return a; }

		///\brief equal operation
		bool operator == (const Vector3D<T>& b) const { if (x == b.x && y == b.y && z == b.z) return true; else return false; }

		///\brief unequal
		bool operator != (const Vector3D<T>& b) const { if (x == b.x && y == b.y && z == b.z) return false; else return true; }

		///\brief assign function
		Vector3D<T>& operator = (const Vector3D<T>& b){ x = b.x; y = b.y; z = b.z; return *this; }

		///\brief assign function
		Vector3D<T>& operator = (T b){ x = b; y = b; z = b; return *this; }

		///\brief assign different type
		template <typename U>
		Vector3D<T>& operator = (const Vector3D<U>& b){x = static_cast<T>(b.x); y = static_cast<T>(b.y); z = static_cast<T>(b.z); return *this; }

		///\brief Perform compound assignment and subtraction by a 3-D vector
		Vector3D<T>& operator -= (const Vector3D<T>& b){ x -= b.x; y -= b.y; z -= b.z; return *this; }

		///\brief Perform compound assignment and addition by a 3-D vector
		Vector3D<T>& operator += (const Vector3D<T>& b){ x += b.x; y += b.y; z += b.z; return *this; }

		///\brief Perform compound assignment and multiplication by a 3-D vector
		Vector3D<T>& operator *= (const Vector3D<T>& b){ x *= b.x; y *= b.y; z *= b.z; return *this; }

		///\brief Perform compound assignment and division by a 3-D vector
		Vector3D<T>& operator /= (const Vector3D<T>& b){ x /= b.x; y /= b.y; z /= b.z; return *this; }

		///\brief Perform compound assignment and addition by a scalar
		Vector3D<T>& operator += (T b){ x += b; y += b; z += b; return *this; }

		///\brief Perform compound assignment and subtraction by a scalar
		Vector3D<T>& operator -= (T b){ x -= b; y -= b; z -= b; return *this; }

		///\brief Perform compound assignment and multiplication by a scalar
		Vector3D<T>& operator *= (T b){ x *= b; y *= b; z *= b; return *this; }

		///\brief Perform compound assignment and division by a scalar
		Vector3D<T>& operator /= (T b){ x /= b; y /= b; z /= b; return *this; }

		/// \brief  Add a 3-D vector by another 3-D vector
		Vector3D<T> operator + (const Vector3D<T>& b) const { Vector3D<T> c; c.x = x + b.x; c.y = y + b.y; c.z = z + b.z; return c; }

		/// \brief  Subtract a 3-D vector by another 3-D vector
		Vector3D<T> operator - (const Vector3D<T>& b) const { Vector3D<T> c; c.x = x - b.x; c.y = y - b.y; c.z = z - b.z; return c; }

		/// \brief  Multiply a 3-D vector by another 3-D vector
		Vector3D<T> operator * (const Vector3D<T>& b) const { Vector3D<T> c; c.x = x * b.x; c.y = y * b.y; c.z = z * b.z; return c; }

		/// \brief  Divide a 3-D vector by another 3-D vector
		Vector3D<T> operator / (const Vector3D<T>& b) const { Vector3D<T> c; c.x = x / b.x; c.y = y / b.y; c.z = z / b.z; return c; }

		/// \brief  Add a 3-D vector by a scalar
		Vector3D<T> operator + (T b) const { Vector3D<T> c; c.x = x + b; c.y = y + b; c.z = z + b; return c; }

		/// \brief  Subtract a 3-D vector by a scalar
		Vector3D<T> operator - (T b) const { Vector3D<T> c; c.x = x - b; c.y = y - b; c.z = z - b; return c; }

		/// \brief  Multiply a 3-D vector by a scalar
		Vector3D<T> operator * (T b) const { Vector3D<T> c; c.x = x * b; c.y = y * b; c.z = z * b; return c; }

		/// \brief  Divide a 3-D vector by a scalar
		Vector3D<T> operator / (T b) const { Vector3D<T> c; c.x = x / b; c.y = y / b; c.z = z / b; return c; }

		/// \brief  Negate all elements of a 3-D point
		Vector3D<T> operator -() const { return Vector3D<T>(0-x, 0-y, 0-z); }

		/// \brief  cross product
		Vector3D<T> operator ^ (const Vector3D<T>& b) const { Vector3D<T> c; c.x = y * b.z - z * b.y; c.y = z * b.x - x * b.z; c.z = x * b.y - y * b.x; return c; } 

		//\brief rotate a vector by a 3*3 matrix
		Vector3D<double> Rotate(const double* dMatrix) const { Vector3D<double> b;	b.x = dMatrix[0] * x + dMatrix[1] * y + dMatrix[2] * z;
		b.y = dMatrix[3] * x + dMatrix[4] * y + dMatrix[5] * z; b.z = dMatrix[6] * x + dMatrix[7] * y + dMatrix[8] * z;	return b;}

	};
    /*template class _MCSFALGO_DATATYPE_API Vector3D<int>;
	template class _MCSFALGO_DATATYPE_API Vector3D<unsigned int>;
	template class _MCSFALGO_DATATYPE_API Vector3D<short>;
	template class _MCSFALGO_DATATYPE_API Vector3D<unsigned short>;
	template class _MCSFALGO_DATATYPE_API Vector3D<float>;
	template class _MCSFALGO_DATATYPE_API Vector3D<double>;
	template class _MCSFALGO_DATATYPE_API Vector3D<char>;
	template class _MCSFALGO_DATATYPE_API Vector3D<unsigned char>;*/


	typedef Vector3D<int> Vector3D_i;
	typedef Vector3D<unsigned int> Vector3D_ui;
	typedef Vector3D<float> Vector3D_f;
	typedef Vector3D<double> Vector3D_d;
	typedef Vector3D<int> Point3D_i;
	typedef Vector3D<unsigned int> Point3D_ui;
	typedef Vector3D<float> Point3D_f;
	typedef Vector3D<double> Point3D_d;

	typedef unsigned int SizeType;
	typedef Vector3D_ui SizeVector;
	typedef double SpacingType;
	typedef Vector3D_d SpacingVector;
}

namespace CbibSeg{

	class SegFunction
	{

	public:
		string gFileName;
		SegFunction(void);
		~SegFunction(void);
		void getTemp(float *temp,int &startpage,int &endPage,int *dim);
		void getGbTemp(float *GbTemp,int &Gbstartpage,int &GbendPage,int *Gbdim);
		void getUIterTemp(float *UIterTemp1,float *UIterTemp2,float *UIterTemp3,float *UIterTemp4,float *UIterTemp5,int &UIterstartpage,int &UIterendPage,int *UIterdim);

		//肝脏分割
		bool liversegment(short *pData_Base,const int *iDimension, const float *fSpace,const bool bMultiThread,int *otherparm,char *pAllMask,bool *bHaveVessel);

		//肝脏八段分割
		//测试，给定三个不在同一平面的点，生成一个平面表达式。（返回四个参数（Ax+By+Cz+D=0））

		//通过一个平面将mask分成两段
		bool seg_mask_8(const char *pAllMask,int* point,char *pMask, const int *iDim);
		bool seg_mask_8(const char *pAllMask,const char *centerLineName,char *cMask,const int *iDim);
		bool seg_mask_8(const char *pAllMask,const int* vein,const int *veinL,const int *veinM, const int *portal, const int* portalL, const int portalLineL,const int portalLineR,char *pMask,const int *iDim);		
		bool seg_mask_8(const char *pAllMask, const vector<vector<TPoint>> &vCenterlines,const vector<TPoint> &vHeader, char *pMask,const int *iDim);	
		bool seg_mask_8_centerline(const char *centerlineName,int* vein, int *vienR, int *veinM,  int* portal,  int* portalL, int* portalLineL,int* portalLineR,int *point);

		void seg_mask_8_1(const int* vein,const int *veinM,const int *portal,char *pMask,const int *iDim);
		void seg_mask_8_2(const int* vein,const int *veinR,const int *portal,char *pMask,const int *iDim);
		void seg_mask_8_3(const int portalLineR,char *pMask,const int *iDim);
		void seg_mask_8_4(const char *pAllMask,const int* vein,const int *portalL,const int *portal,char *pMask,const int *iDim);
		void seg_mask_8_5(const int portalLineL, char *pMask,const int *iDim);
		
		//void Tran_seg_mask_8_3(const int portalLineR,char *pMask,const int *iDim,const int *iTranOriginal);
		//const char* centerlineName;
		
		void seg_CaudateLobe(char *pMask_2_3, const int *iDim);//分割肝尾叶
		void seg_CaudateLobe_manual(char *pMask_2_3, int *iTranOriginal, const int *iDim);//分割肝尾叶
		void seg_CaudateLobe(char *pMask_2_3, int *iTranOriginal, const int *iDim);//分割肝尾叶
		void seg_CaudateLobe(const int* pointa,const int *pointb,const int *pointc,char *pMask,const int *iDim); //分割肝尾叶
		void seg_CaudateLobe2(const int* pointa,const int *pointb,const int *pointc,int &portalLineR,char *pMask,const int *iDim); //分割肝尾叶第二刀
		void SegFunction::Minivalue(char *pMask,float *data,const int *iDim);
		void SegFunction::rotate(char *pMask,const int *iDim,const int *veinPoint,const int *portalPoint,const int *portalL);
		void corrosion(char *afterFlag,char *flag,int mark1,int mark2,const int *iDim);
		bool is_connect(char *mask,char *temp,int mark1,int mark2,const int *iDim,int &change);
		//char* translateTran(int* iTranOriginal, int *iTranDim, short *pData_Base, char *pMask8, const int *iDim);  // 平移变换函数
		char* translateTran(int *iTranOriginal, int *iTranDim, char *pMask8, const int *iDim);  // 平移变换函数
		char* translateTranReverse(int *iTranOriginal, const int *iTranDim, char *pTranMask, char *pMask8, const int *iDim);  // 平移逆变换函数
		void DisGraph(char *mask,int *dis,const int *iDim);
		bool roundValue(char *mask,int position,int value,const int *iDim);
		bool roundValue(int *dis,int position,int value,const int *iDim);
		bool maxPoint(float *result,int x,int y,int z,const int *iDim);
		bool minPoint(float *result,int x,int y,int z,const int *iDim);
		bool maxPoint(float *newdata,int x,int y,const int *iDimension);
		double pointToLine(int *point,int *start,int *end, int *iTranOriginal);
		double pointToLine(int *point,int *a,int *b);
		double pointToPoint(int *point,int *portal);
		bool WaterShedNew(int *pSrc, unsigned char * SeedImage, char * pDst,const int *iDim,char * m_pMask,int num);
		bool WaterShed2D(unsigned char *pSrc,unsigned char * SeedImage,char * pDst,char *mask2D,const int *iDim,int num);
		//需要提交的子函数
		template<typename T>
		void writeData(T *mask,string name,const int *iDim);
		
	
		void GrowOnPoint(float *mask,char *mask8,int *point,const int *iDim);
		//主要的函数
		void find_liverLocation();
		void pre_processing(int iGain,bool bCut,int iStart,int iEnd,bool bInterpolation,float fnorm);
		void gmac3D();
		void post_processing(const int* iDimension,bool bSeed,bool cutflag,int istart,int iend);         
		void region_grow2(int radio);
		void calDistance(std::queue<int> *leftS,int *lDistance,char *afterFlag,char *flag,const int *iDim);
		
		//肿瘤分割
		void seg_tumour(const int *seed,short *pData_base,const char *pAllMask, int* iDimension,const float * fSpace,char *pMask);
		void seg_tumour_in(const int *seed,short *pData_base,const char *pAllMask,int* iDimension,const float * fSpace,char *pMask);
		void get_tumour_Features(const short *pData_base, const int *iDimension,const float *fSpace,const char *pMask,float *fFeatures);
	
	private:
		//辅助用函数
		void StackSort(stack<int>& s, int *pSrc);
		void init();
		bool initParm();
		void showParm();
		bool initParm(char * filename);
		void region_grow(int* pSeed,char *pMask,const int *iDim);
		void region_grow(int* pSeed,float thre);
		void region_grow_new(float thre);
		void find_seed_U();
		void interpolation2ori(int *iDimension);
		void pre_threshold(int iGain,int iCT);
		void interpolation(float fNorm);
		void cut_page(int iStart,int iEnd);
		void cvtCut2ori(int iStart,int iEnd,const int* iDim);
		void Gaussian_2D(float *smatrix,int wid,int heigh,int nKsize,float gama,float* matrix);
		void localMaximun(float * H,int wid, int heigh, int *xIn,int *yIn,int& PointNum);
		void smooth(int model );

		bool saveBmp(char *bmpName, unsigned char *imgBuf, int width, int height, int biBitCount);
		//bool saveBmp(char *bmpName, float *imgBuf, int width, int height, int biBitCount);
		bool dumpBmp(char *dirName, unsigned char *imgBufSet, int width, int height, int num ,int biBitCount);

		void writeRaw(char *cMaskName,short* pAllMask,int wid,int height,int page)
		{
			FILE *fp;
			fopen_s(&fp,cMaskName,"wb");
			fwrite(pAllMask,sizeof(short),wid*height*page,fp);
			fclose(fp);


		}
		void writeRaw(char *cMaskName,char*cInfo,float* pAllMask,int wid,int height,int page)
		{
			FILE *fp;
			fopen_s(&fp,cMaskName,"wb");
			fwrite(pAllMask,sizeof(float),wid*height*page,fp);
			fclose(fp);

			fopen_s(&fp,cInfo,"wb");
			fprintf(fp,"%d %d %d ",wid,height,page);
			fclose(fp);

		}
		//gmac用函数
		void DataTransformation( float* data, int size );
		void InitUV( float* data, float* _u, float* _v);
		void Gradient( float* data, int width, int height, int depth,float* NormGrad );
		void Forwardx( float* data, float* dz, int width, int height, int depth );
		void Forwardy( float* data, float* dz, int width, int height, int depth );
		void Forwardz( float* data, float* dz, int width, int height, int depth );
		void Backwardx( float* data, float* dz, int width, int height, int depth );
		void Backwardy( float* data, float* dz, int width, int height, int depth );
		void Backwardz( float* data, float* dz, int width, int height, int depth);
		void ComputeGb( float* data, int width, int height, int depth ,float *gb,float* NormGrand);
		void Gaussian_3D(float * dataSet,int Ng,float gama,float* matrix);
		void Gaussian_3D(float * dataSet,int Ng,float gama,float* matrix, const int *Dim); // 给定iDimension
		void conv_aid(float *x, float* h, int lenX, int lenH, float* result);
		void conv(float *x, float *h, int lenX, int lenH, float* result);

		//八段分割辅助函数
		int generate_plane_3point(const int *a,const int *b,const int *c,int *plane);
		bool find_place(int *a,int*b,int *aim,float& cosValue);

		void copyPlane(int *dst,int *src)
		{
			for(int i=0;i<4;i++)
			{
				dst[i]=src[i];
			}
		}
		void copypoint(int *dst,int *src)
		{
			for(int i=0;i<3;i++)
			{
				dst[i]=src[i];
			}
		}
		void swapPoint(int *a,int *b)
		{
			int t[3];
			memcpy(t,a,3*sizeof(int));
			memcpy(a,b,3*sizeof(int));
			memcpy(b,t,3*sizeof(int));
		}


		//输出需要分割的图片

		short *pData_temp;

		char *pMask_temp;

		int tempNum;
		int iDimX;
		int iDimY;
		int iDimZ;
		int pSeed[3];
		int iStart;
		int iEnd;
		int centrePoint[3];
		int veinPoint[3];
		int portalPoint[3];
		int searchLen;
		int iLiverCT;


		float fSpaceX;
		float fSpaceY;
		float fSpaceZ;
		bool bHaveVessel;
		bool bMultiThread;
		int* otherparm;
		//肝时期特有参数
		int iContrastFlag;//造影剂使用标记
		int iMaxIm;

		//find_eigenValue
		//找肝特诊点即所在位置用参数
		int iCurdeHigh;//初始阈值上界
		int iCurdeLow;//初始阈值下界
		int iCuredeRange;//上下界的差
		int iGuassian2DSize;//2D高斯模板大小；
		float iGuassian2DGamga;//2D高斯gama值；
		int iLocalLowerBound;//局部最小值下界
		int iLocalPage;//局部最小值page值。
		int iMinDis;//局部最小值距离。

		//预处理用参数
		int iGain;
		float fNorm;//分辨率

		//后期处理用参数
		float fReginGrowParm;

		//gmac辅助用参数
		float fStdGbParm;
		float fBataParm;
		float fThetaParm;
		float fLambdaParm;
		float fDtParm;
		float fStdPwmParm;
		float fNgParm;
		int iNbIterUpdateParm;
		int iIterationCountParm;
		float fThreU;


		//gmac用参数
		float std_Gb;
		float beta;
		float theta;
		float lambda;
		float dt;
		float gv;
		float std_pwm;
		int NbIterUpdate;
		float *gb;
		float* f;    

		float* dx;
		float* dy;
		float* dz;

		float* u;//作为最终结果
		float* v;//作为处理结果


		float* pxu;
		float* pyu;
		float* pzu;

		float* divp;

		float* term;

		float* termx;
		float* termy;
		float* termz;

		float* regionTermIn;
		float* regionTermOut;
		float* RegionTerm;
		int iterationCount;
		int updateInterval;

		int* HistIn;
		int* HistOut;
		float* result;
		float* PdfIn;
		float* PdfOut;

		float* Gb;
		float* NormGrad;
		//	float* G1D;
		float* sMatrix;

		float* temp;
		int tempDim[3];

		float* Gbtemp;

		float* UIterationtemp1;
		float* UIterationtemp2;
		float* UIterationtemp3;
		float* UIterationtemp4;
		float* UIterationtemp5;


	};
}
#endif
