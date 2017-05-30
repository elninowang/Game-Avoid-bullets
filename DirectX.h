#define			SafeRelease(x)		if(x){x->Release();x=NULL;}
//global variares
LPGUID						lpGUID=NULL;
LPDIRECTDRAW7				lpDD=NULL;
LPDIRECTDRAWCLIPPER			lpClip=NULL;
LPDIRECTDRAWSURFACE7		lpDDPri=NULL;
LPDIRECTDRAWSURFACE7		lpDDBack=NULL;
LPDIRECTDRAWSURFACE7		lpDDBackGround=NULL;
LPDIRECTDRAWSURFACE7		lpDDPlane=NULL;
LPDIRECTDRAWSURFACE7		lpDDBlock=NULL;


//LPDIRECTDRAWSURFACE7		lpDDTemp=NULL;


//Load Bitmap for Surface;
LPDIRECTDRAWSURFACE7 bitmap_surface(LPCTSTR file_name)
{
	HBITMAP hBitmap;
	BITMAP bitmap;
	LPDIRECTDRAWSURFACE7 surf;

	//hBitmap=(HBITMAP)LoadBitmap(NULL,file_name);
	hBitmap=(HBITMAP) LoadImage(NULL,file_name,IMAGE_BITMAP,0,0,
								LR_DEFAULTSIZE|LR_LOADFROMFILE);
	if( !hBitmap)
	{
		MessageBox(NULL,TEXT("NO Bitmap!"),TEXT("WRONG"),NULL);
		return NULL;
	}
	GetObject(hBitmap,sizeof(BITMAP),&bitmap);
	int cxBitmap=bitmap.bmWidth;
	int cyBitmap=bitmap.bmHeight;
 
	HRESULT ddrval;
	DDSURFACEDESC2 ddsd;
	ZeroMemory(&ddsd,sizeof(ddsd));
	ddsd.dwSize = sizeof(DDSURFACEDESC2);
	ddsd.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT ;
	ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN|DDSCAPS_SYSTEMMEMORY; 
	ddsd.dwWidth = cxBitmap;
	ddsd.dwHeight = cyBitmap;

	ddrval=lpDD->CreateSurface(&ddsd,&surf,NULL);
	if( ddrval != DD_OK )
	{
		MessageBox(NULL,TEXT("Surface Create Wrong!"),TEXT("WRONG"),NULL);
		return NULL;;
	}
	else
	{
		surf->GetDC(&hdc);
		HDC hdcMem=CreateCompatibleDC(hdc);
		SelectObject(hdcMem,hBitmap);
		BitBlt(hdc,0,0,cxBitmap,cyBitmap,hdcMem,0,0,SRCCOPY);

		surf->ReleaseDC(hdc);
		DeleteDC(hdcMem);
	}
	DeleteObject(hBitmap);
	return surf;
}

//global function 
void DrawDirectX(HWND hWnd);
//Create or Delete  
HRESULT	InitDirectX(HWND hWnd)
{
	int ddrval;
	DDSURFACEDESC2 ddsd;
	
	ddrval = DirectDrawCreateEx( lpGUID,(VOID**)(&lpDD),IID_IDirectDraw7,NULL);
	if( ddrval != DD_OK )
	{
		MessageBox(hWnd,TEXT("DirectDrawCreateWrong!"),TEXT("WRONG"),NULL);
		return FALSE;
	}
	ddrval = lpDD->SetCooperativeLevel(hWnd, DDSCL_NORMAL );
	if( ddrval != DD_OK )
	{
		MessageBox(hWnd,TEXT("CooperativeCreateWrong!"),TEXT("WRONG"),NULL);
		return FALSE;
	}
	ddrval = lpDD->CreateClipper(NULL,&lpClip,NULL);
	if( ddrval != DD_OK )
	{
		MessageBox(hWnd,TEXT("ClipperCreateWrong!"),TEXT("WRONG"),NULL);
		return FALSE;
	}
	lpClip->SetHWnd(0,hWnd);

	ZeroMemory(&ddsd,sizeof(ddsd));
	ddsd.dwSize = sizeof(ddsd);
	ddsd.dwFlags = DDSD_CAPS;
	ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;
	ddrval = lpDD->CreateSurface(&ddsd,&lpDDPri,NULL);
	if( ddrval != DD_OK )
	{
		MessageBox(hWnd,TEXT("PrimarySurfaceCreateWrong!"),TEXT("WRONG"),NULL);
		return FALSE;
	}
	lpDDPri->SetClipper(lpClip);

	ZeroMemory(&ddsd,sizeof(ddsd));
	ddsd.dwSize = sizeof(ddsd);
	ddsd.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT ;
	ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN|DDSCAPS_SYSTEMMEMORY; 
	ddsd.dwWidth = cxSurface;
	ddsd.dwHeight = cySurface;

	ddrval=lpDD->CreateSurface(&ddsd,&lpDDBack,NULL);
	if( ddrval != DD_OK )
	{
		MessageBox(hWnd,TEXT("Surface Create Wrong!"),TEXT("WRONG"),NULL);
		return FALSE;
	}
		
	lpDDBackGround = bitmap_surface( "BackGound.bmp" );
	lpDDPlane = bitmap_surface( "Plane.bmp" );
	lpDDBlock = bitmap_surface( "Block.bmp" );

	DDPIXELFORMAT ddpf;
	ddpf.dwSize = sizeof(ddpf);
	lpDDPri->GetPixelFormat(&ddpf);

	int KeyColor = ddpf.dwGBitMask;
	DDCOLORKEY key;
	key.dwColorSpaceLowValue = KeyColor;
	key.dwColorSpaceHighValue = KeyColor;
	lpDDPlane->SetColorKey(DDCKEY_SRCBLT, &key);
	lpDDBlock->SetColorKey(DDCKEY_SRCBLT, &key);

	DrawDirectX(hWnd);
	return TRUE;
}
void CleanUp()
{
	SafeRelease( lpDDBlock );
	SafeRelease( lpDDBack );
	SafeRelease( lpDDBackGround );
	SafeRelease( lpDDBack );
	SafeRelease( lpDDPri );
	SafeRelease( lpClip );
}
void DrawDirectX(HWND hWnd)
{
	RECT rect,rect1;
	
	POINT point;
	point.x=0;
	point.y=0;
	ClientToScreen(hWnd,&point);
	rect.top=0;
	rect.left=0;
	rect.bottom=cySurface;
	rect.right=cxSurface;
	rect1.top=point.y;
	rect1.left=point.x;
	rect1.bottom=point.y+cySurface;
	rect1.right=point.x+cxSurface;
	//lpDDBack->Blt(&rect ,lpDDBackGround, &rect, DDBLT_WAIT, NULL );
	lpDDBack->BltFast(0, 0, lpDDBackGround, NULL , DDBLTFAST_WAIT );
	Draw();
	
	lpDDPri->Blt(&rect1, lpDDBack,&rect, DDBLT_WAIT, NULL);
}