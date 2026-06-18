// Original Name : vase_rend_draft_1.h

/* Drawing nearly perfect 2D line segments in OpenGL
 * You can use this code however you want.
 * I just hope you to cite my name and the page of this technique:
 * http://artgrammer.blogspot.com/2011/05/drawing-nearly-perfect-2d-line-segments.html
 * http://www.codeproject.com/KB/openGL/gllinedraw.aspx
 * 
 * Enjoy. Chris Tsang.*/
#ifndef VASE_REN_DRAFT_H
#define VASE_REN_DRAFT_H
#include <math.h>
static inline ::f64 GET_ABS(::f64 x) {return x>0?x:-x;}
/*
 * this implementation uses only basic gl (opengl 1.0)
 *   renders in immediate mode by glBegin/ glEnd
 *   choose only 1 from vase_rend_draft_1.h and vase_rend_draft_2.h
 *   to your need. if you have no preference, just use vase_rend_draft_2.h
 */
/* this is the master line() function which features:
 * -premium quality anti-aliased line drawing
 * -smaller CPU overhead than other CPU rasterizing algorithms
 * -line thickness control
 * -line color control
 * -can choose to use alpha blend or not
 * 
 * sample usage using alpha blending:
 * 
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glMatrixMode(GL_PROJECTION);
  glPushxxxxMatrix();
	glLoadIdentity();
	glOrtho( 0,context_width,context_height,0,0.0f,100.0f);

		line ( 10,100,100,300,		//coordinates
			1.2,			//thickness in px
			0.5, 0.0, 1.0, 1.0,	//line color RGBA
			0,0,			//not used
			true);			//enable alphablend

		//more line() calls and other drawing code...
  glPopMatrix();
  glDisable(GL_BLEND); //restore blending options
 *
 * and not using alpha blending (blend to background color):
 *
  glMatrixMode(GL_PROJECTION);
  glPushxxxxMatrix();
	glLoadIdentity();
	glOrtho( 0,context_width,context_height,0,0.0f,100.0f);

		line ( 20,100,110,300,		//coordinates
			1.2,			//thickness in px
			0.5, 0.0, 1.0,		//line color *rgb*
			1.0, 1.0, 1.0,		//background color
			false);			//not using alphablend

		//more line() calls and other drawing code...
  glPopMatrix();
*/
void line( ::f64 x1, ::f64 y1, ::f64 x2, ::f64 y2, //coordinates of the line
	::f32 w, //width/thickness of the line in pixel
	::f32 Cr, ::f32 Cg, ::f32 Cb, //rgb color components
	::f32 Br, ::f32 Bg, ::f32 Bb, //color of background when alphablend=false,
					//Br=alpha of color when alphablend=true
	bool alphablend) //use alpha blend or not
{
	::f64 t; ::f64 R; ::f64 f=w-static_cast<::i32>(w);
	::f32 A;
	
	if ( alphablend)
		A=Br;
	else
		A=1.0f;
	
	//determine parameters t,R
	/*   */if ( w>=0.0 && w<1.0) {
		t=0.05; R=0.48+0.32*f;
		if ( !alphablend) {
			Cr+=0.88*(1-f);
			Cg+=0.88*(1-f);
			Cb+=0.88*(1-f);
			if ( Cr>1.0) Cr=1.0;
			if ( Cg>1.0) Cg=1.0;
			if ( Cb>1.0) Cb=1.0;
		} else {
			A*=f;
		}
	} else if ( w>=1.0 && w<2.0) {
		t=0.05+f*0.33; R=0.768+0.312*f;
	} else if ( w>=2.0 && w<3.0){
		t=0.38+f*0.58; R=1.08;
	} else if ( w>=3.0 && w<4.0){
		t=0.96+f*0.48; R=1.08;
	} else if ( w>=4.0 && w<5.0){
		t=1.44+f*0.46; R=1.08;
	} else if ( w>=5.0 && w<6.0){
		t=1.9+f*0.6; R=1.08;
	} else if ( w>=6.0){
		::f64 ff=w-6.0;
		t=2.5+ff*0.50; R=1.08;
	}
	//printf( "w=%f, f=%f, C=%.4f\n", w,f,C);
	
	//determine angle of the line to horizontal
	::f64 tx=0,ty=0; //aura thinkness of a line
	::f64 Rx=0,Ry=0; //fading edge of a line
	::f64 cx=0,cy=0; //cap of a line
	::f64 ALW=0.01;
	::f64 Δx=x2-x1;
	::f64 Δy=y2-y1;
	if ( GET_ABS(Δx) < ALW) {
		//vertical
		tx=t; ty=0;
		Rx=R; Ry=0;
		if ( w>0.0 && w<=1.0) { //m:2
			tx = 0.5; Rx=0.0;
		}
	} else if ( GET_ABS(Δy) < ALW) {
		//horizontal
		tx=0; ty=t;
		Rx=0; Ry=R;
		if ( w>0.0 && w<=1.0) {
			ty = 0.5; Ry=0.0;
		}
	} else {
		if ( w < 3) { //approximate to make things even faster
			::f64 m=Δy/Δx;
			//and calculate tx,ty,Rx,Ry
			if ( m>-0.4142 && m<=0.4142) {
				// -22.5< angle <= 22.5, approximate to 0 (degree)
				tx=t*0.1; ty=t;
				Rx=R*0.6; Ry=R;
			} else if ( m>0.4142 && m<=2.4142) {
				// 22.5< angle <= 67.5, approximate to 45 (degree)
				tx=t*-0.7071; ty=t*0.7071;
				Rx=R*-0.7071; Ry=R*0.7071;
			} else if ( m>2.4142 || m<=-2.4142) {
				// 67.5 < angle <=112.5, approximate to 90 (degree)
				tx=t; ty=t*0.1;
				Rx=R; Ry=R*0.6;
			} else if ( m>-2.4142 && m<-0.4142) {
				// 112.5 < angle < 157.5, approximate to 135 (degree)
				tx=t*0.7071; ty=t*0.7071;
				Rx=R*0.7071; Ry=R*0.7071;
			} else {
				// error in determining angle
				//printf( "error in determining angle: m=%.4f\n",m);
			}
		} else { //calculate to exact
			Δx=y1-y2;
			Δy=x2-x1;
			::f64 L=sqrt(Δx*Δx+Δy*Δy);
			Δx/=L;
			Δy/=L;
			cx=-Δy; cy=Δx; //m:3
			tx=t*Δx; ty=t*Δy;
			Rx=R*Δx; Ry=R*Δy;
		}
	}
	
	x1+=cx*0.5; y1+=cy*0.5; //m:4
	x2-=cx*0.5; y2-=cy*0.5;
	
	//draw the line by triangle strip m:1
glBegin(GL_TRIANGLE_STRIP);
	if ( !alphablend) {glColor3f( Br,Bg,Bb);} else {glColor4f( Cr,Cg,Cb, 0);}
	glVertex2f( x1-tx-Rx-cx, y1-ty-Ry-cy); //fading edge
	glVertex2f( x2-tx-Rx+cx, y2-ty-Ry+cy);
	
	if ( !alphablend) {glColor3f( Cr,Cg,Cb);} else {glColor4f( Cr,Cg,Cb, A);}
	glVertex2f( x1-tx-cx,y1-ty-cy); //aura
	glVertex2f( x2-tx+cx,y2-ty+cy);
	glVertex2f( x1+tx-cx,y1+ty-cy);
	glVertex2f( x2+tx+cx,y2+ty+cy);
	
	if ( !alphablend) {glColor3f( Br,Bg,Bb);} else {glColor4f( Cr,Cg,Cb, 0);}
	glVertex2f( x1+tx+Rx-cx, y1+ty+Ry-cy); //fading edge
	glVertex2f( x2+tx+Rx+cx, y2+ty+Ry+cy);
glEnd();

	//cap
	if ( w < 3) {
		//do not draw cap
	} else {
		//draw cap
	glBegin(GL_TRIANGLE_STRIP);
		if ( !alphablend) {glColor3f( Br,Bg,Bb);} else {glColor4f( Cr,Cg,Cb, 0);}
		glVertex2f( x1-tx-Rx-cx, y1-ty-Ry-cy);
		glVertex2f( x1-tx-Rx, y1-ty-Ry);
		if ( !alphablend) {glColor3f( Cr,Cg,Cb);} else {glColor4f( Cr,Cg,Cb, A);}
		glVertex2f( x1-tx-cx, y1-ty-cy);
		if ( !alphablend) {glColor3f( Br,Bg,Bb);} else {glColor4f( Cr,Cg,Cb, 0);}
		glVertex2f( x1+tx+Rx, y1+ty+Ry);
		if ( !alphablend) {glColor3f( Cr,Cg,Cb);} else {glColor4f( Cr,Cg,Cb, A);}
		glVertex2f( x1+tx-cx, y1+ty-cy);
		if ( !alphablend) {glColor3f( Br,Bg,Bb);} else {glColor4f( Cr,Cg,Cb, 0);}
		glVertex2f( x1+tx+Rx-cx, y1+ty+Ry-cy);
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
		if ( !alphablend) {glColor3f( Br,Bg,Bb);} else {glColor4f( Cr,Cg,Cb, 0);}
		glVertex2f( x2-tx-Rx+cx, y2-ty-Ry+cy);
		glVertex2f( x2-tx-Rx, y2-ty-Ry);
		if ( !alphablend) {glColor3f( Cr,Cg,Cb);} else {glColor4f( Cr,Cg,Cb, A);}
		glVertex2f( x2-tx+cx, y2-ty+cy);
		if ( !alphablend) {glColor3f( Br,Bg,Bb);} else {glColor4f( Cr,Cg,Cb, 0);}
		glVertex2f( x2+tx+Rx, y2+ty+Ry);
		if ( !alphablend) {glColor3f( Cr,Cg,Cb);} else {glColor4f( Cr,Cg,Cb, A);}
		glVertex2f( x2+tx+cx, y2+ty+cy);
		if ( !alphablend) {glColor3f( Br,Bg,Bb);} else {glColor4f( Cr,Cg,Cb, 0);}
		glVertex2f( x2+tx+Rx+cx, y2+ty+Ry+cy);
	glEnd();
	}
}


/*a skimmed version of line(); no color, no thickness control
 * draws near-perfectly a black "hair line" of thickness 1px
 * when alphablend is false, it assumes drawing on a white surface
 * when alphablend is true, it draws with alpha */
void hair_line( ::f64 x1, ::f64 y1, ::f64 x2, ::f64 y2, bool alphablend=0)
{
	::f64 t=0.05; ::f64 R=0.768;
	::f64 C=0.0;

	//determine angle of the line to horizontal
	::f64 tx=0,ty=0, Rx=0,Ry=0;
	::f64 ALW=0.01;
	::f64 Δx=x2-x1;
	::f64 Δy=y2-y1;
	if ( GET_ABS(Δx) < ALW) {
		//vertical
		tx = 0.5; ty = 0.0;
		Rx = 0.0; Ry = 0.0;
	} else if ( GET_ABS(Δy) < ALW) {
		//horizontal
		tx = 0.0; ty = 0.5;
		Rx = 0.0; Ry = 0.0;
	} else {
		::f64 m=Δy/Δx;
		if ( m>-0.4142 && m<=0.4142) {
			// -22.5< angle <= 22.5, approximate to 0 (degree)
			tx=t*0.1; ty=t;
			Rx=R*0.6; Ry=R;
		} else if ( m>0.4142 && m<=2.4142) {
			// 22.5< angle <= 67.5, approximate to 45 (degree)
			tx=t*-0.7071; ty=t*0.7071;
			Rx=R*-0.7071; Ry=R*0.7071;
		} else if ( m>2.4142 || m<=-2.4142) {
			// 67.5 < angle <=112.5, approximate to 90 (degree)
			tx=t; ty=t*0.1;
			Rx=R; Ry=R*0.6;
		} else if ( m>-2.4142 && m<-0.4142) {
			// 112.5 < angle < 157.5, approximate to 135 (degree)
			tx=t*0.7071; ty=t*0.7071;
			Rx=R*0.7071; Ry=R*0.7071;
		}
	}
	
	//draw the line by triangle strip
glBegin(GL_TRIANGLE_STRIP);
	if ( !alphablend) {glColor3f( 1,1,1);} else {glColor4f( C,C,C, 0);}
	glVertex2f( x1-tx-Rx, y1-ty-Ry); //fading edge
	glVertex2f( x2-tx-Rx, y2-ty-Ry);
	
	glColor3f( C,C,C);	
	glVertex2f( x1-tx,y1-ty); //aura
	glVertex2f( x2-tx,y2-ty);
	glVertex2f( x1+tx,y1+ty);
	glVertex2f( x2+tx,y2+ty);
	
	if ( !alphablend) {glColor3f( 1,1,1);} else {glColor4f( C,C,C, 0);}
	glVertex2f( x1+tx+Rx, y1+ty+Ry); //fading edge
	glVertex2f( x2+tx+Rx, y2+ty+Ry);
glEnd();
}

/*as a fall back of line()*/
void line_raw( ::f64 x1, ::f64 y1, ::f64 x2, ::f64 y2,
	::f64 w,
	::f64 Cr, ::f64 Cg, ::f64 Cb,
	::f64,::f64,::f64, bool)
{
	glLineWidth(w);
glBegin(GL_LINES);
	glColor3f( Cr,Cg,Cb);
	glVertex2f( x1,y1);
	glVertex2f( x2,y2);
glEnd();
}

#endif
