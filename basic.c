/* Copyright (c) 2016 youka

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgement in the product documentation would be
   appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution. */

#include "basic.h"

const void *_basic_offset=(const void*)(3*sizeof(float));

byte _basic_init=0;

unint _basic_p=0;
struct {
	int pview, pos, tc;
	int col, texmode, texmap;

	int noise_tex, window_fbo;
	int floor_fbo, floor_dist;
} _basic_pv;

byte init_basic(void)
{
	if(!_basic_init)
	{
		_basic_p=glCreateProgram();
		if(load_pro(_basic_p,"vs.glsl","fs.glsl"))
		{
			mat4 mat;

			glUseProgram(_basic_p);

			_basic_pv.pview=glGetUniformLocation(_basic_p,"pview");
			_basic_pv.pos=glGetAttribLocation(_basic_p,"pos");
			_basic_pv.tc=glGetAttribLocation(_basic_p,"tc");

			_basic_pv.col=glGetUniformLocation(_basic_p,"col");
			_basic_pv.texmode=glGetUniformLocation(_basic_p,"texmode");
			_basic_pv.texmap=glGetUniformLocation(_basic_p,"texmap");

			_basic_pv.noise_tex=glGetUniformLocation(_basic_p,"noise_tex");
			_basic_pv.window_fbo=glGetUniformLocation(_basic_p,"window_fbo");
			_basic_pv.floor_fbo=glGetUniformLocation(_basic_p,"floor_fbo");
			_basic_pv.floor_dist=glGetUniformLocation(_basic_p,"floor_dist");

			idmat(mat);
			send_pview(mat);
			glEnableVertexAttribArray(_basic_pv.pos);
			glEnableVertexAttribArray(_basic_pv.tc);

			send_col(v1());
			texmode(0);
			glUniform1i(_basic_pv.texmap,0);
			glActiveTexture(GL_TEXTURE0);

			glUniform1i(_basic_pv.noise_tex,1);
			glUniform1i(_basic_pv.window_fbo,2);
			glUniform1i(_basic_pv.floor_fbo,3);
			glUniform1i(_basic_pv.floor_dist,4);

			_basic_init=1;
		}
		else
		{
			glDeleteProgram(_basic_p);
			info("Program not created\n");
		}
	}

	return _basic_init;
}

void done_basic(void)
{
	if(_basic_init)
	{
		glDeleteProgram(_basic_p);
		_basic_init=0;
	}
}

void send_pview(const mat4 mat)
{
	glUniformMatrix4fv(_basic_pv.pview,1,GL_FALSE,(const float*)mat);
}

void send_attribs(void)
{
	glVertexAttribPointer(_basic_pv.pos,3,GL_FLOAT,GL_FALSE,stride,NULL);
	glVertexAttribPointer(_basic_pv.tc,2,GL_FLOAT,GL_FALSE,stride,_basic_offset);
}

void send_col(vec4 col)
{
	glUniform4fv(_basic_pv.col,1,(const float*)&col);
}

void texmode(int mode)
{
	glUniform1i(_basic_pv.texmode,mode);
}
