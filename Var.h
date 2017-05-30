#define		BLOCK_NUM		40
#define		MAXV			3
#define     MAXPV			6
#define		AV				1

HWND hWnd;
int cxClient;
int cyClient;
int cxSurface = 454;
int cySurface = 340;
int cxPlane = 38;
int cyPlane = 36;
int cxBlock = 6;
int cyBlock = 6;
HDC hdc;
HPEN hpen;
HBRUSH hbrush;

Plane pl(cxSurface/2,cySurface/2);
Block bl[BLOCK_NUM];

LONGLONG RealTime = 0;
