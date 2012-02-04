
#ifndef _CGL3MACRO_H
#define _CGL3MACRO_H

#ifdef __gl_h_
  #error Can not include both gl.h and CGL3Macro.h simultaneously
#endif

#include <OpenGL/CGLTypes.h>
#include <OpenGL/CGLContext.h>
#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>

/* Macro context name (CGLContextObj) */
#if !defined(CGL_MACRO_CONTEXT)
  #define CGL_MACRO_CONTEXT cgl_ctx
#endif

/* Macro renderer name (GLIContext) */
#if !defined(CGL_MACRO_RENDERER)
  #define CGL_MACRO_RENDERER cgl_rend
#endif

#define CGL_MACRO_DECLARE_CONTEXT()  CGLContextObj CGL_MACRO_CONTEXT = CGLGetCurrentContext();

/* Repeated renderer lookups may be avoided by defining CGL_MACRO_CACHE_RENDERER before including CGLMacro.h.
 Note: If you change the value of CGL_MACRO_CONTEXT partway through a function, you will have to
 keep CGL_MACRO_RENDERER up to date with with it's context. */
#if defined(CGL_MACRO_CACHE_RENDERER)
  #define CGL_MACRO_DECLARE_RENDERER()  GLIContext CGL_MACRO_RENDERER = CGL_MACRO_CONTEXT->rend;
  #define CGL_MACRO_CONTEXT_RENDERER  CGL_MACRO_RENDERER
#else
  #define CGL_MACRO_DECLARE_RENDERER()
  #define CGL_MACRO_CONTEXT_RENDERER  CGL_MACRO_CONTEXT->rend
#endif

/* Use the following function macro to declare the local CGLMacro variables */
#define CGL_MACRO_DECLARE_VARIABLES() \
    CGL_MACRO_DECLARE_CONTEXT(); \
    CGL_MACRO_DECLARE_RENDERER();

/* This is for converting old non-arb handle definitions to ARB handle definitions for 64 bit compiles */
#define CGL_HANDLE_ARB(handle)	(GLhandleARB)((unsigned long)handle)

// Generated content.
#define glCullFace(mode) \
    (*(CGL_MACRO_CONTEXT)->disp.cull_face)(CGL_MACRO_CONTEXT_RENDERER, mode)

#define glFrontFace(mode) \
    (*(CGL_MACRO_CONTEXT)->disp.front_face)(CGL_MACRO_CONTEXT_RENDERER, mode)

#define glHint(target, mode) \
    (*(CGL_MACRO_CONTEXT)->disp.hint)(CGL_MACRO_CONTEXT_RENDERER, target, mode)

#define glLineWidth(width) \
    (*(CGL_MACRO_CONTEXT)->disp.line_width)(CGL_MACRO_CONTEXT_RENDERER, width)

#define glPointSize(size) \
    (*(CGL_MACRO_CONTEXT)->disp.point_size)(CGL_MACRO_CONTEXT_RENDERER, size)

#define glPolygonMode(face, mode) \
    (*(CGL_MACRO_CONTEXT)->disp.polygon_mode)(CGL_MACRO_CONTEXT_RENDERER, face, mode)

#define glScissor(x, y, width, height) \
    (*(CGL_MACRO_CONTEXT)->disp.scissor)(CGL_MACRO_CONTEXT_RENDERER, x, y, width, height)

#define glTexParameterf(target, pname, param) \
    (*(CGL_MACRO_CONTEXT)->disp.tex_parameterf)(CGL_MACRO_CONTEXT_RENDERER, target, pname, param)

#define glTexParameterfv(target, pname, params) \
    (*(CGL_MACRO_CONTEXT)->disp.tex_parameterfv)(CGL_MACRO_CONTEXT_RENDERER, target, pname, params)

#define glTexParameteri(target, pname, param) \
    (*(CGL_MACRO_CONTEXT)->disp.tex_parameteri)(CGL_MACRO_CONTEXT_RENDERER, target, pname, param)

#define glTexParameteriv(target, pname, params) \
    (*(CGL_MACRO_CONTEXT)->disp.tex_parameteriv)(CGL_MACRO_CONTEXT_RENDERER, target, pname, params)

#define glTexImage1D(target, level, internalformat, width, border, format, type, pixels) \
    (*(CGL_MACRO_CONTEXT)->disp.tex_image1D)(CGL_MACRO_CONTEXT_RENDERER, target, level, internalformat, width, border, format, type, pixels)

#define glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels) \
    (*(CGL_MACRO_CONTEXT)->disp.tex_image2D)(CGL_MACRO_CONTEXT_RENDERER, target, level, internalformat, width, height, border, format, type, pixels)

#define glDrawBuffer(mode) \
    (*(CGL_MACRO_CONTEXT)->disp.draw_buffer)(CGL_MACRO_CONTEXT_RENDERER, mode)

#define glClear(mask) \
    (*(CGL_MACRO_CONTEXT)->disp.clear)(CGL_MACRO_CONTEXT_RENDERER, mask)

#define glClearColor(red, green, blue, alpha) \
    (*(CGL_MACRO_CONTEXT)->disp.clear_color)(CGL_MACRO_CONTEXT_RENDERER, red, green, blue, alpha)

#define glClearStencil(s) \
    (*(CGL_MACRO_CONTEXT)->disp.clear_stencil)(CGL_MACRO_CONTEXT_RENDERER, s)

#define glClearDepth(depth) \
    (*(CGL_MACRO_CONTEXT)->disp.clear_depth)(CGL_MACRO_CONTEXT_RENDERER, depth)

#define glStencilMask(mask) \
    (*(CGL_MACRO_CONTEXT)->disp.stencil_mask)(CGL_MACRO_CONTEXT_RENDERER, mask)

#define glColorMask(red, green, blue, alpha) \
    (*(CGL_MACRO_CONTEXT)->disp.color_mask)(CGL_MACRO_CONTEXT_RENDERER, red, green, blue, alpha)

#define glDepthMask(flag) \
    (*(CGL_MACRO_CONTEXT)->disp.depth_mask)(CGL_MACRO_CONTEXT_RENDERER, flag)

#define glDisable(cap) \
    (*(CGL_MACRO_CONTEXT)->disp.disable)(CGL_MACRO_CONTEXT_RENDERER, cap)

#define glEnable(cap) \
    (*(CGL_MACRO_CONTEXT)->disp.enable)(CGL_MACRO_CONTEXT_RENDERER, cap)

#define glFinish() \
    (*(CGL_MACRO_CONTEXT)->disp.finish)(CGL_MACRO_CONTEXT_RENDERER)

#define glFlush() \
    (*(CGL_MACRO_CONTEXT)->disp.flush)(CGL_MACRO_CONTEXT_RENDERER)

#define glBlendFunc(sfactor, dfactor) \
    (*(CGL_MACRO_CONTEXT)->disp.blend_func)(CGL_MACRO_CONTEXT_RENDERER, sfactor, dfactor)

#define glLogicOp(opcode) \
    (*(CGL_MACRO_CONTEXT)->disp.logic_op)(CGL_MACRO_CONTEXT_RENDERER, opcode)

#define glStencilFunc(func, ref, mask) \
    (*(CGL_MACRO_CONTEXT)->disp.stencil_func)(CGL_MACRO_CONTEXT_RENDERER, func, ref, mask)

#define glStencilOp(fail, zfail, zpass) \
    (*(CGL_MACRO_CONTEXT)->disp.stencil_op)(CGL_MACRO_CONTEXT_RENDERER, fail, zfail, zpass)

#define glDepthFunc(func) \
    (*(CGL_MACRO_CONTEXT)->disp.depth_func)(CGL_MACRO_CONTEXT_RENDERER, func)

#define glPixelStoref(pname, param) \
    (*(CGL_MACRO_CONTEXT)->disp.pixel_storef)(CGL_MACRO_CONTEXT_RENDERER, pname, param)

#define glPixelStorei(pname, param) \
    (*(CGL_MACRO_CONTEXT)->disp.pixel_storei)(CGL_MACRO_CONTEXT_RENDERER, pname, param)

#define glReadBuffer(mode) \
    (*(CGL_MACRO_CONTEXT)->disp.read_buffer)(CGL_MACRO_CONTEXT_RENDERER, mode)

#define glReadPixels(x, y, width, height, format, type, pixels) \
    (*(CGL_MACRO_CONTEXT)->disp.read_pixels)(CGL_MACRO_CONTEXT_RENDERER, x, y, width, height, format, type, pixels)

#define glGetBooleanv(pname, params) \
    (*(CGL_MACRO_CONTEXT)->disp.get_booleanv)(CGL_MACRO_CONTEXT_RENDERER, pname, params)

#define glGetDoublev(pname, params) \
    (*(CGL_MACRO_CONTEXT)->disp.get_doublev)(CGL_MACRO_CONTEXT_RENDERER, pname, params)

#define glGetError() \
    (*(CGL_MACRO_CONTEXT)->disp.get_error)(CGL_MACRO_CONTEXT_RENDERER)

#define glGetFloatv(pname, params) \
    (*(CGL_MACRO_CONTEXT)->disp.get_floatv)(CGL_MACRO_CONTEXT_RENDERER, pname, params)

#define glGetIntegerv(pname, params) \
    (*(CGL_MACRO_CONTEXT)->disp.get_integerv)(CGL_MACRO_CONTEXT_RENDERER, pname, params)

#define glGetString(name) \
    (*(CGL_MACRO_CONTEXT)->disp.get_string)(CGL_MACRO_CONTEXT_RENDERER, name)

#define glGetTexImage(target, level, format, type, pixels) \
    (*(CGL_MACRO_CONTEXT)->disp.get_tex_image)(CGL_MACRO_CONTEXT_RENDERER, target, level, format, type, pixels)

#define glGetTexParameterfv(target, pname, params) \
    (*(CGL_MACRO_CONTEXT)->disp.get_tex_parameterfv)(CGL_MACRO_CONTEXT_RENDERER, target, pname, params)

#define glGetTexParameteriv(target, pname, params) \
    (*(CGL_MACRO_CONTEXT)->disp.get_tex_parameteriv)(CGL_MACRO_CONTEXT_RENDERER, target, pname, params)

#define glGetTexLevelParameterfv(target, level, pname, params) \
    (*(CGL_MACRO_CONTEXT)->disp.get_tex_level_parameterfv)(CGL_MACRO_CONTEXT_RENDERER, target, level, pname, params)

#define glGetTexLevelParameteriv(target, level, pname, params) \
    (*(CGL_MACRO_CONTEXT)->disp.get_tex_level_parameteriv)(CGL_MACRO_CONTEXT_RENDERER, target, level, pname, params)

#define glIsEnabled(cap) \
    (*(CGL_MACRO_CONTEXT)->disp.is_enabled)(CGL_MACRO_CONTEXT_RENDERER, cap)

#define glDepthRange(near, far) \
    (*(CGL_MACRO_CONTEXT)->disp.depth_range)(CGL_MACRO_CONTEXT_RENDERER, near, far)

#define glViewport(x, y, width, height) \
    (*(CGL_MACRO_CONTEXT)->disp.viewport)(CGL_MACRO_CONTEXT_RENDERER, x, y, width, height)

#define glDrawArrays(mode, first, count) \
    (*(CGL_MACRO_CONTEXT)->disp.draw_arrays)(CGL_MACRO_CONTEXT_RENDERER, mode, first, count)

#define glDrawElements(mode, count, type, indices) \
    (*(CGL_MACRO_CONTEXT)->disp.draw_elements)(CGL_MACRO_CONTEXT_RENDERER, mode, count, type, indices)

#define glPolygonOffset(factor, units) \
    (*(CGL_MACRO_CONTEXT)->disp.polygon_offset)(CGL_MACRO_CONTEXT_RENDERER, factor, units)

#define glCopyTexImage1D(target, level, internalformat, x, y, width, border) \
    (*(CGL_MACRO_CONTEXT)->disp.copy_tex_image1D)(CGL_MACRO_CONTEXT_RENDERER, target, level, internalformat, x, y, width, border)

#define glCopyTexImage2D(target, level, internalformat, x, y, width, height, border) \
    (*(CGL_MACRO_CONTEXT)->disp.copy_tex_image2D)(CGL_MACRO_CONTEXT_RENDERER, target, level, internalformat, x, y, width, height, border)

#define glCopyTexSubImage1D(target, level, xoffset, x, y, width) \
    (*(CGL_MACRO_CONTEXT)->disp.copy_tex_sub_image1D)(CGL_MACRO_CONTEXT_RENDERER, target, level, xoffset, x, y, width)

#define glCopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height) \
    (*(CGL_MACRO_CONTEXT)->disp.copy_tex_sub_image2D)(CGL_MACRO_CONTEXT_RENDERER, target, level, xoffset, yoffset, x, y, width, height)

#define glTexSubImage1D(target, level, xoffset, width, format, type, pixels) \
    (*(CGL_MACRO_CONTEXT)->disp.tex_sub_image1D)(CGL_MACRO_CONTEXT_RENDERER, target, level, xoffset, width, format, type, pixels)

#define glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels) \
    (*(CGL_MACRO_CONTEXT)->disp.tex_sub_image2D)(CGL_MACRO_CONTEXT_RENDERER, target, level, xoffset, yoffset, width, height, format, type, pixels)

#define glBindTexture(target, texture) \
    (*(CGL_MACRO_CONTEXT)->disp.bind_texture)(CGL_MACRO_CONTEXT_RENDERER, target, texture)

#define glDeleteTextures(n, textures) \
    (*(CGL_MACRO_CONTEXT)->disp.delete_textures)(CGL_MACRO_CONTEXT_RENDERER, n, textures)

#define glGenTextures(n, textures) \
    (*(CGL_MACRO_CONTEXT)->disp.gen_textures)(CGL_MACRO_CONTEXT_RENDERER, n, textures)

#define glIsTexture(texture) \
    (*(CGL_MACRO_CONTEXT)->disp.is_texture)(CGL_MACRO_CONTEXT_RENDERER, texture)

#define glBlendColor(red, green, blue, alpha) \
    (*(CGL_MACRO_CONTEXT)->disp.blend_color)(CGL_MACRO_CONTEXT_RENDERER, red, green, blue, alpha)

#define glBlendEquation(mode) \
    (*(CGL_MACRO_CONTEXT)->disp.blend_equation)(CGL_MACRO_CONTEXT_RENDERER, mode)

#define glDrawRangeElements(mode, start, end, count, type, indices) \
    (*(CGL_MACRO_CONTEXT)->disp.draw_range_elements)(CGL_MACRO_CONTEXT_RENDERER, mode, start, end, count, type, indices)

#define glTexImage3D(target, level, internalformat, width, height, depth, border, format, type, pixels) \
    (*(CGL_MACRO_CONTEXT)->disp.tex_image3D)(CGL_MACRO_CONTEXT_RENDERER, target, level, internalformat, width, height, depth, border, format, type, pixels)

#define glTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels) \
    (*(CGL_MACRO_CONTEXT)->disp.tex_sub_image3D)(CGL_MACRO_CONTEXT_RENDERER, target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels)

#define glCopyTexSubImage3D(target, level, xoffset, yoffset, zoffset, x, y, width, height) \
    (*(CGL_MACRO_CONTEXT)->disp.copy_tex_sub_image3D)(CGL_MACRO_CONTEXT_RENDERER, target, level, xoffset, yoffset, zoffset, x, y, width, height)

#define glActiveTexture(texture) \
    (*(CGL_MACRO_CONTEXT)->disp.active_texture)(CGL_MACRO_CONTEXT_RENDERER, texture)

#define glSampleCoverage(value, invert) \
    (*(CGL_MACRO_CONTEXT)->disp.sample_coverage)(CGL_MACRO_CONTEXT_RENDERER, value, invert)

#define glCompressedTexImage3D(target, level, internalformat, width, height, depth, border, imageSize, data) \
    (*(CGL_MACRO_CONTEXT)->disp.compressed_tex_image3D)(CGL_MACRO_CONTEXT_RENDERER, target, level, internalformat, width, height, depth, border, imageSize, data)

#define glCompressedTexImage2D(target, level, internalformat, width, height, border, imageSize, data) \
    (*(CGL_MACRO_CONTEXT)->disp.compressed_tex_image2D)(CGL_MACRO_CONTEXT_RENDERER, target, level, internalformat, width, height, border, imageSize, data)

#define glCompressedTexImage1D(target, level, internalformat, width, border, imageSize, data) \
    (*(CGL_MACRO_CONTEXT)->disp.compressed_tex_image1D)(CGL_MACRO_CONTEXT_RENDERER, target, level, internalformat, width, border, imageSize, data)

#define glCompressedTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data) \
    (*(CGL_MACRO_CONTEXT)->disp.compressed_tex_sub_image3D)(CGL_MACRO_CONTEXT_RENDERER, target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data)

#define glCompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, format, imageSize, data) \
    (*(CGL_MACRO_CONTEXT)->disp.compressed_tex_sub_image2D)(CGL_MACRO_CONTEXT_RENDERER, target, level, xoffset, yoffset, width, height, format, imageSize, data)

#define glCompressedTexSubImage1D(target, level, xoffset, width, format, imageSize, data) \
    (*(CGL_MACRO_CONTEXT)->disp.compressed_tex_sub_image1D)(CGL_MACRO_CONTEXT_RENDERER, target, level, xoffset, width, format, imageSize, data)

#define glGetCompressedTexImage(target, level, img) \
    (*(CGL_MACRO_CONTEXT)->disp.get_compressed_tex_image)(CGL_MACRO_CONTEXT_RENDERER, target, level, img)

#define glBlendFuncSeparate(sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha) \
    (*(CGL_MACRO_CONTEXT)->disp.blend_func_separate)(CGL_MACRO_CONTEXT_RENDERER, sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha)

#define glMultiDrawArrays(mode, first, count, primcount) \
    (*(CGL_MACRO_CONTEXT)->disp.multi_draw_arrays)(CGL_MACRO_CONTEXT_RENDERER, mode, first, count, primcount)

#define glMultiDrawElements(mode, count, type, indices, primcount) \
    (*(CGL_MACRO_CONTEXT)->disp.multi_draw_elements)(CGL_MACRO_CONTEXT_RENDERER, mode, count, type, indices, primcount)

#define glPointParameterf(pname, param) \
    (*(CGL_MACRO_CONTEXT)->disp.point_parameterf)(CGL_MACRO_CONTEXT_RENDERER, pname, param)

#define glPointParameterfv(pname, params) \
    (*(CGL_MACRO_CONTEXT)->disp.point_parameterfv)(CGL_MACRO_CONTEXT_RENDERER, pname, params)

#define glPointParameteri(pname, param) \
    (*(CGL_MACRO_CONTEXT)->disp.point_parameteri)(CGL_MACRO_CONTEXT_RENDERER, pname, param)

#define glPointParameteriv(pname, params) \
    (*(CGL_MACRO_CONTEXT)->disp.point_parameteriv)(CGL_MACRO_CONTEXT_RENDERER, pname, params)

#define glGenQueries(n, ids) \
    (*(CGL_MACRO_CONTEXT)->disp.gen_queries)(CGL_MACRO_CONTEXT_RENDERER, n, ids)

#define glDeleteQueries(n, ids) \
    (*(CGL_MACRO_CONTEXT)->disp.delete_queries)(CGL_MACRO_CONTEXT_RENDERER, n, ids)

#define glIsQuery(id) \
    (*(CGL_MACRO_CONTEXT)->disp.is_query)(CGL_MACRO_CONTEXT_RENDERER, id)

#define glBeginQuery(target, id) \
    (*(CGL_MACRO_CONTEXT)->disp.begin_query)(CGL_MACRO_CONTEXT_RENDERER, target, id)

#define glEndQuery(target) \
    (*(CGL_MACRO_CONTEXT)->disp.end_query)(CGL_MACRO_CONTEXT_RENDERER, target)

#define glGetQueryiv(target, pname, params) \
    (*(CGL_MACRO_CONTEXT)->disp.get_queryiv)(CGL_MACRO_CONTEXT_RENDERER, target, pname, params)

#define glGetQueryObjectiv(id, pname, params) \
    (*(CGL_MACRO_CONTEXT)->disp.get_query_objectiv)(CGL_MACRO_CONTEXT_RENDERER, id, pname, params)

#define glGetQueryObjectuiv(id, pname, params) \
    (*(CGL_MACRO_CONTEXT)->disp.get_query_objectuiv)(CGL_MACRO_CONTEXT_RENDERER, id, pname, params)

#define glBindBuffer(target, buffer) \
    (*(CGL_MACRO_CONTEXT)->disp.bind_buffer)(CGL_MACRO_CONTEXT_RENDERER, target, buffer)

#define glDeleteBuffers(n, buffers) \
    (*(CGL_MACRO_CONTEXT)->disp.delete_buffers)(CGL_MACRO_CONTEXT_RENDERER, n, buffers)

#define glGenBuffers(n, buffers) \
    (*(CGL_MACRO_CONTEXT)->disp.gen_buffers)(CGL_MACRO_CONTEXT_RENDERER, n, buffers)

#define glIsBuffer(buffer) \
    (*(CGL_MACRO_CONTEXT)->disp.is_buffer)(CGL_MACRO_CONTEXT_RENDERER, buffer)

#define glBufferData(target, size, data, usage) \
    (*(CGL_MACRO_CONTEXT)->disp.buffer_data)(CGL_MACRO_CONTEXT_RENDERER, target, size, data, usage)

#define glBufferSubData(target, offset, size, data) \
    (*(CGL_MACRO_CONTEXT)->disp.buffer_sub_data)(CGL_MACRO_CONTEXT_RENDERER, target, offset, size, data)

#define glGetBufferSubData(target, offset, size, data) \
    (*(CGL_MACRO_CONTEXT)->disp.get_buffer_sub_data)(CGL_MACRO_CONTEXT_RENDERER, target, offset, size, data)

#define glMapBuffer(target, access) \
    (*(CGL_MACRO_CONTEXT)->disp.map_buffer)(CGL_MACRO_CONTEXT_RENDERER, target, access)

#define glUnmapBuffer(target) \
    (*(CGL_MACRO_CONTEXT)->disp.unmap_buffer)(CGL_MACRO_CONTEXT_RENDERER, target)

#define glGetBufferParameteriv(target, pname, params) \
    (*(CGL_MACRO_CONTEXT)->disp.get_buffer_parameteriv)(CGL_MACRO_CONTEXT_RENDERER, target, pname, params)

#define glGetBufferPointerv(target, pname, params) \
    (*(CGL_MACRO_CONTEXT)->disp.get_buffer_pointerv)(CGL_MACRO_CONTEXT_RENDERER, target, pname, params)

#define glBlendEquationSeparate(modeRGB, modeAlpha) \
    (*(CGL_MACRO_CONTEXT)->disp.blend_equation_separate_EXT)(CGL_MACRO_CONTEXT_RENDERER, modeRGB, modeAlpha)

#define glDrawBuffers(n, bufs) \
    (*(CGL_MACRO_CONTEXT)->disp.draw_buffers_ARB)(CGL_MACRO_CONTEXT_RENDERER, n, bufs)

#define glStencilOpSeparate(face, sfail, dpfail, dppass) \
    (*(CGL_MACRO_CONTEXT)->disp.stencil_op_separate_ATI)(CGL_MACRO_CONTEXT_RENDERER, face, sfail, dpfail, dppass)

#define glStencilFuncSeparate(face, func, ref, mask) \
    (*(CGL_MACRO_CONTEXT)->disp.stencil_func_separate)(CGL_MACRO_CONTEXT_RENDERER, face, func, ref, mask)

#define glStencilMaskSeparate(face, mask) \
    (*(CGL_MACRO_CONTEXT)->disp.stencil_mask_separate)(CGL_MACRO_CONTEXT_RENDERER, face, mask)

#define glAttachShader(program, shader) \
    (*(CGL_MACRO_CONTEXT)->disp.attach_object_ARB)(CGL_MACRO_CONTEXT_RENDERER, CGL_HANDLE_ARB(program), CGL_HANDLE_ARB(shader))

#define glBindAttribLocation(program, index, name) \
    (*(CGL_MACRO_CONTEXT)->disp.bind_attrib_location_ARB)(CGL_MACRO_CONTEXT_RENDERER, CGL_HANDLE_ARB(program), index, name)

#define glCompileShader(shader) \
    (*(CGL_MACRO_CONTEXT)->disp.compile_shader_ARB)(CGL_MACRO_CONTEXT_RENDERER, CGL_HANDLE_ARB(shader))

#define glCreateProgram() \
    (GLuint)((unsigned long)(*(CGL_MACRO_CONTEXT)->disp.create_program_object_ARB)(CGL_MACRO_CONTEXT_RENDERER))

#define glCreateShader(type) \
    (GLuint)((unsigned long)(*(CGL_MACRO_CONTEXT)->disp.create_shader_object_ARB)(CGL_MACRO_CONTEXT_RENDERER, type))

#define glDeleteProgram(program) \
    (*(CGL_MACRO_CONTEXT)->disp.delete_object_ARB)(CGL_MACRO_CONTEXT_RENDERER, CGL_HANDLE_ARB(program))

#define glDeleteShader(shader) \
    (*(CGL_MACRO_CONTEXT)->disp.delete_object_ARB)(CGL_MACRO_CONTEXT_RENDERER, CGL_HANDLE_ARB(shader))

#define glDetachShader(program, shader) \
    (*(CGL_MACRO_CONTEXT)->disp.detach_object_ARB)(CGL_MACRO_CONTEXT_RENDERER, CGL_HANDLE_ARB(program), CGL_HANDLE_ARB(shader))

#define glDisableVertexAttribArray(index) \
    (*(CGL_MACRO_CONTEXT)->disp.disable_vertex_attrib_array_ARB)(CGL_MACRO_CONTEXT_RENDERER, index)

#define glEnableVertexAttribArray(index) \
    (*(CGL_MACRO_CONTEXT)->disp.enable_vertex_attrib_array_ARB)(CGL_MACRO_CONTEXT_RENDERER, index)

#define glGetActiveAttrib(program, index, bufSize, length, size, type, name) \
    (*(CGL_MACRO_CONTEXT)->disp.get_active_attrib_ARB)(CGL_MACRO_CONTEXT_RENDERER, CGL_HANDLE_ARB(program), index, bufSize, length, size, type, name)

#define glGetActiveUniform(program, index, bufSize, length, size, type, name) \
    (*(CGL_MACRO_CONTEXT)->disp.get_active_uniform_ARB)(CGL_MACRO_CONTEXT_RENDERER, CGL_HANDLE_ARB(program), index, bufSize, length, size, type, name)

#define glGetAttachedShaders(program, maxCount, count, obj) \
    (*(CGL_MACRO_CONTEXT)->disp.get_attached_shaders)(CGL_MACRO_CONTEXT_RENDERER, program, maxCount, count, obj)

#define glGetAttribLocation(program, name) \
    (*(CGL_MACRO_CONTEXT)->disp.get_attrib_location_ARB)(CGL_MACRO_CONTEXT_RENDERER, CGL_HANDLE_ARB(program), name)

#define glGetProgramiv(program, pname, params) \
    (*(CGL_MACRO_CONTEXT)->disp.get_programiv)(CGL_MACRO_CONTEXT_RENDERER, program, pname, params)

#define glGetProgramInfoLog(program, bufSize, length, infoLog) \
    (*(CGL_MACRO_CONTEXT)->disp.get_program_info_log)(CGL_MACRO_CONTEXT_RENDERER, program, bufSize, length, infoLog)

#define glGetShaderiv(shader, pname, params) \
    (*(CGL_MACRO_CONTEXT)->disp.get_shaderiv)(CGL_MACRO_CONTEXT_RENDERER, shader, pname, params)

#define glGetShaderInfoLog(shader, bufSize, length, infoLog) \
    (*(CGL_MACRO_CONTEXT)->disp.get_shader_info_log)(CGL_MACRO_CONTEXT_RENDERER, shader, bufSize, length, infoLog)

#define glGetShaderSource(shader, bufSize, length, source) \
    (*(CGL_MACRO_CONTEXT)->disp.get_shader_source_ARB)(CGL_MACRO_CONTEXT_RENDERER, CGL_HANDLE_ARB(shader), bufSize, length, source)

#define glGetUniformLocation(program, name) \
    (*(CGL_MACRO_CONTEXT)->disp.get_uniform_location_ARB)(CGL_MACRO_CONTEXT_RENDERER, CGL_HANDLE_ARB(program), name)

#define glGetUniformfv(program, location, params) \
    (*(CGL_MACRO_CONTEXT)->disp.get_uniformfv_ARB)(CGL_MACRO_CONTEXT_RENDERER, CGL_HANDLE_ARB(program), location, params)

#define glGetUniformiv(program, location, params) \
    (*(CGL_MACRO_CONTEXT)->disp.get_uniformiv_ARB)(CGL_MACRO_CONTEXT_RENDERER, CGL_HANDLE_ARB(program), location, params)

#define glGetVertexAttribdv(index, pname, params) \
    (*(CGL_MACRO_CONTEXT)->disp.get_vertex_attribdv_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, pname, params)

#define glGetVertexAttribfv(index, pname, params) \
    (*(CGL_MACRO_CONTEXT)->disp.get_vertex_attribfv_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, pname, params)

#define glGetVertexAttribiv(index, pname, params) \
    (*(CGL_MACRO_CONTEXT)->disp.get_vertex_attribiv_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, pname, params)

#define glGetVertexAttribPointerv(index, pname, pointer) \
    (*(CGL_MACRO_CONTEXT)->disp.get_vertex_attrib_pointerv_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, pname, pointer)

#define glIsProgram(program) \
    (*(CGL_MACRO_CONTEXT)->disp.is_program)(CGL_MACRO_CONTEXT_RENDERER, program)

#define glIsShader(shader) \
    (*(CGL_MACRO_CONTEXT)->disp.is_shader)(CGL_MACRO_CONTEXT_RENDERER, shader)

#define glLinkProgram(program) \
    (*(CGL_MACRO_CONTEXT)->disp.link_program_ARB)(CGL_MACRO_CONTEXT_RENDERER, CGL_HANDLE_ARB(program))

#define glShaderSource(shader, count, string, length) \
    (*(CGL_MACRO_CONTEXT)->disp.shader_source_ARB)(CGL_MACRO_CONTEXT_RENDERER, CGL_HANDLE_ARB(shader), count, string, length)

#define glUseProgram(program) \
    (*(CGL_MACRO_CONTEXT)->disp.use_program_object_ARB)(CGL_MACRO_CONTEXT_RENDERER, CGL_HANDLE_ARB(program))

#define glUniform1f(location, v0) \
    (*(CGL_MACRO_CONTEXT)->disp.uniform1f_ARB)(CGL_MACRO_CONTEXT_RENDERER, location, v0)

#define glUniform2f(location, v0, v1) \
    (*(CGL_MACRO_CONTEXT)->disp.uniform2f_ARB)(CGL_MACRO_CONTEXT_RENDERER, location, v0, v1)

#define glUniform3f(location, v0, v1, v2) \
    (*(CGL_MACRO_CONTEXT)->disp.uniform3f_ARB)(CGL_MACRO_CONTEXT_RENDERER, location, v0, v1, v2)

#define glUniform4f(location, v0, v1, v2, v3) \
    (*(CGL_MACRO_CONTEXT)->disp.uniform4f_ARB)(CGL_MACRO_CONTEXT_RENDERER, location, v0, v1, v2, v3)

#define glUniform1i(location, v0) \
    (*(CGL_MACRO_CONTEXT)->disp.uniform1i_ARB)(CGL_MACRO_CONTEXT_RENDERER, location, v0)

#define glUniform2i(location, v0, v1) \
    (*(CGL_MACRO_CONTEXT)->disp.uniform2i_ARB)(CGL_MACRO_CONTEXT_RENDERER, location, v0, v1)

#define glUniform3i(location, v0, v1, v2) \
    (*(CGL_MACRO_CONTEXT)->disp.uniform3i_ARB)(CGL_MACRO_CONTEXT_RENDERER, location, v0, v1, v2)

#define glUniform4i(location, v0, v1, v2, v3) \
    (*(CGL_MACRO_CONTEXT)->disp.uniform4i_ARB)(CGL_MACRO_CONTEXT_RENDERER, location, v0, v1, v2, v3)

#define glUniform1fv(location, count, value) \
    (*(CGL_MACRO_CONTEXT)->disp.uniform1fv_ARB)(CGL_MACRO_CONTEXT_RENDERER, location, count, value)

#define glUniform2fv(location, count, value) \
    (*(CGL_MACRO_CONTEXT)->disp.uniform2fv_ARB)(CGL_MACRO_CONTEXT_RENDERER, location, count, value)

#define glUniform3fv(location, count, value) \
    (*(CGL_MACRO_CONTEXT)->disp.uniform3fv_ARB)(CGL_MACRO_CONTEXT_RENDERER, location, count, value)

#define glUniform4fv(location, count, value) \
    (*(CGL_MACRO_CONTEXT)->disp.uniform4fv_ARB)(CGL_MACRO_CONTEXT_RENDERER, location, count, value)

#define glUniform1iv(location, count, value) \
    (*(CGL_MACRO_CONTEXT)->disp.uniform1iv_ARB)(CGL_MACRO_CONTEXT_RENDERER, location, count, value)

#define glUniform2iv(location, count, value) \
    (*(CGL_MACRO_CONTEXT)->disp.uniform2iv_ARB)(CGL_MACRO_CONTEXT_RENDERER, location, count, value)

#define glUniform3iv(location, count, value) \
    (*(CGL_MACRO_CONTEXT)->disp.uniform3iv_ARB)(CGL_MACRO_CONTEXT_RENDERER, location, count, value)

#define glUniform4iv(location, count, value) \
    (*(CGL_MACRO_CONTEXT)->disp.uniform4iv_ARB)(CGL_MACRO_CONTEXT_RENDERER, location, count, value)

#define glUniformMatrix2fv(location, count, transpose, value) \
    (*(CGL_MACRO_CONTEXT)->disp.uniform_matrix2fv_ARB)(CGL_MACRO_CONTEXT_RENDERER, location, count, transpose, value)

#define glUniformMatrix3fv(location, count, transpose, value) \
    (*(CGL_MACRO_CONTEXT)->disp.uniform_matrix3fv_ARB)(CGL_MACRO_CONTEXT_RENDERER, location, count, transpose, value)

#define glUniformMatrix4fv(location, count, transpose, value) \
    (*(CGL_MACRO_CONTEXT)->disp.uniform_matrix4fv_ARB)(CGL_MACRO_CONTEXT_RENDERER, location, count, transpose, value)

#define glValidateProgram(program) \
    (*(CGL_MACRO_CONTEXT)->disp.validate_program_ARB)(CGL_MACRO_CONTEXT_RENDERER, CGL_HANDLE_ARB(program))

#define glVertexAttrib1d(index, x) \
    (*(CGL_MACRO_CONTEXT)->disp.vertex_attrib1d_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, x)

#define glVertexAttrib1dv(index, v) \
    (*(CGL_MACRO_CONTEXT)->disp.vertex_attrib1dv_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, v)

#define glVertexAttrib1f(index, x) \
    (*(CGL_MACRO_CONTEXT)->disp.vertex_attrib1f_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, x)

#define glVertexAttrib1fv(index, v) \
    (*(CGL_MACRO_CONTEXT)->disp.vertex_attrib1fv_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, v)

#define glVertexAttrib1s(index, x) \
    (*(CGL_MACRO_CONTEXT)->disp.vertex_attrib1s_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, x)

#define glVertexAttrib1sv(index, v) \
    (*(CGL_MACRO_CONTEXT)->disp.vertex_attrib1sv_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, v)

#define glVertexAttrib2d(index, x, y) \
    (*(CGL_MACRO_CONTEXT)->disp.vertex_attrib2d_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, x, y)

#define glVertexAttrib2dv(index, v) \
    (*(CGL_MACRO_CONTEXT)->disp.vertex_attrib2dv_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, v)

#define glVertexAttrib2f(index, x, y) \
    (*(CGL_MACRO_CONTEXT)->disp.vertex_attrib2f_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, x, y)

#define glVertexAttrib2fv(index, v) \
    (*(CGL_MACRO_CONTEXT)->disp.vertex_attrib2fv_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, v)

#define glVertexAttrib2s(index, x, y) \
    (*(CGL_MACRO_CONTEXT)->disp.vertex_attrib2s_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, x, y)

#define glVertexAttrib2sv(index, v) \
    (*(CGL_MACRO_CONTEXT)->disp.vertex_attrib2sv_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, v)

#define glVertexAttrib3d(index, x, y, z) \
    (*(CGL_MACRO_CONTEXT)->disp.vertex_attrib3d_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, x, y, z)

#define glVertexAttrib3dv(index, v) \
    (*(CGL_MACRO_CONTEXT)->disp.vertex_attrib3dv_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, v)

#define glVertexAttrib3f(index, x, y, z) \
    (*(CGL_MACRO_CONTEXT)->disp.vertex_attrib3f_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, x, y, z)

#define glVertexAttrib3fv(index, v) \
    (*(CGL_MACRO_CONTEXT)->disp.vertex_attrib3fv_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, v)

#define glVertexAttrib3s(index, x, y, z) \
    (*(CGL_MACRO_CONTEXT)->disp.vertex_attrib3s_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, x, y, z)

#define glVertexAttrib3sv(index, v) \
    (*(CGL_MACRO_CONTEXT)->disp.vertex_attrib3sv_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, v)

#define glVertexAttrib4Nbv(index, v) \
    (*(CGL_MACRO_CONTEXT)->disp.vertex_attrib4Nbv_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, v)

#define glVertexAttrib4Niv(index, v) \
    (*(CGL_MACRO_CONTEXT)->disp.vertex_attrib4Niv_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, v)

#define glVertexAttrib4Nsv(index, v) \
    (*(CGL_MACRO_CONTEXT)->disp.vertex_attrib4Nsv_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, v)

#define glVertexAttrib4Nub(index, x, y, z, w) \
    (*(CGL_MACRO_CONTEXT)->disp.vertex_attrib4Nub_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, x, y, z, w)

#define glVertexAttrib4Nubv(index, v) \
    (*(CGL_MACRO_CONTEXT)->disp.vertex_attrib4Nubv_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, v)

#define glVertexAttrib4Nuiv(index, v) \
    (*(CGL_MACRO_CONTEXT)->disp.vertex_attrib4Nuiv_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, v)

#define glVertexAttrib4Nusv(index, v) \
    (*(CGL_MACRO_CONTEXT)->disp.vertex_attrib4Nusv_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, v)

#define glVertexAttrib4bv(index, v) \
    (*(CGL_MACRO_CONTEXT)->disp.vertex_attrib4bv_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, v)

#define glVertexAttrib4d(index, x, y, z, w) \
    (*(CGL_MACRO_CONTEXT)->disp.vertex_attrib4d_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, x, y, z, w)

#define glVertexAttrib4dv(index, v) \
    (*(CGL_MACRO_CONTEXT)->disp.vertex_attrib4dv_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, v)

#define glVertexAttrib4f(index, x, y, z, w) \
    (*(CGL_MACRO_CONTEXT)->disp.vertex_attrib4f_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, x, y, z, w)

#define glVertexAttrib4fv(index, v) \
    (*(CGL_MACRO_CONTEXT)->disp.vertex_attrib4fv_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, v)

#define glVertexAttrib4iv(index, v) \
    (*(CGL_MACRO_CONTEXT)->disp.vertex_attrib4iv_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, v)

#define glVertexAttrib4s(index, x, y, z, w) \
    (*(CGL_MACRO_CONTEXT)->disp.vertex_attrib4s_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, x, y, z, w)

#define glVertexAttrib4sv(index, v) \
    (*(CGL_MACRO_CONTEXT)->disp.vertex_attrib4sv_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, v)

#define glVertexAttrib4ubv(index, v) \
    (*(CGL_MACRO_CONTEXT)->disp.vertex_attrib4ubv_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, v)

#define glVertexAttrib4uiv(index, v) \
    (*(CGL_MACRO_CONTEXT)->disp.vertex_attrib4uiv_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, v)

#define glVertexAttrib4usv(index, v) \
    (*(CGL_MACRO_CONTEXT)->disp.vertex_attrib4usv_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, v)

#define glVertexAttribPointer(index, size, type, normalized, stride, pointer) \
    (*(CGL_MACRO_CONTEXT)->disp.vertex_attrib_pointer_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, size, type, normalized, stride, pointer)

#define glUniformMatrix2x3fv(location, count, transpose, value) \
    (*(CGL_MACRO_CONTEXT)->disp.uniform_matrix2x3fv)(CGL_MACRO_CONTEXT_RENDERER, location, count, transpose, value)

#define glUniformMatrix3x2fv(location, count, transpose, value) \
    (*(CGL_MACRO_CONTEXT)->disp.uniform_matrix3x2fv)(CGL_MACRO_CONTEXT_RENDERER, location, count, transpose, value)

#define glUniformMatrix2x4fv(location, count, transpose, value) \
    (*(CGL_MACRO_CONTEXT)->disp.uniform_matrix2x4fv)(CGL_MACRO_CONTEXT_RENDERER, location, count, transpose, value)

#define glUniformMatrix4x2fv(location, count, transpose, value) \
    (*(CGL_MACRO_CONTEXT)->disp.uniform_matrix4x2fv)(CGL_MACRO_CONTEXT_RENDERER, location, count, transpose, value)

#define glUniformMatrix3x4fv(location, count, transpose, value) \
    (*(CGL_MACRO_CONTEXT)->disp.uniform_matrix3x4fv)(CGL_MACRO_CONTEXT_RENDERER, location, count, transpose, value)

#define glUniformMatrix4x3fv(location, count, transpose, value) \
    (*(CGL_MACRO_CONTEXT)->disp.uniform_matrix4x3fv)(CGL_MACRO_CONTEXT_RENDERER, location, count, transpose, value)

#define glColorMaski(index, r, g, b, a) \
    (*(CGL_MACRO_CONTEXT)->disp.color_mask_indexed_EXT)(CGL_MACRO_CONTEXT_RENDERER, index, r, g, b, a)

#define glGetBooleani_v(target, index, data) \
    (*(CGL_MACRO_CONTEXT)->disp.get_boolean_indexedv_EXT)(CGL_MACRO_CONTEXT_RENDERER, target, index, data)

#define glGetIntegeri_v(target, index, data) \
    (*(CGL_MACRO_CONTEXT)->disp.get_integer_indexedv_EXT)(CGL_MACRO_CONTEXT_RENDERER, target, index, data)

#define glEnablei(target, index) \
    (*(CGL_MACRO_CONTEXT)->disp.enable_indexed_EXT)(CGL_MACRO_CONTEXT_RENDERER, target, index)

#define glDisablei(target, index) \
    (*(CGL_MACRO_CONTEXT)->disp.disable_indexed_EXT)(CGL_MACRO_CONTEXT_RENDERER, target, index)

#define glIsEnabledi(target, index) \
    (*(CGL_MACRO_CONTEXT)->disp.is_enabled_indexed_EXT)(CGL_MACRO_CONTEXT_RENDERER, target, index)

#define glBeginTransformFeedback(primitiveMode) \
    (*(CGL_MACRO_CONTEXT)->disp.begin_transform_feedback_EXT)(CGL_MACRO_CONTEXT_RENDERER, primitiveMode)

#define glEndTransformFeedback() \
    (*(CGL_MACRO_CONTEXT)->disp.end_transform_feedback_EXT)(CGL_MACRO_CONTEXT_RENDERER)

#define glBindBufferRange(target, index, buffer, offset, size) \
    (*(CGL_MACRO_CONTEXT)->disp.bind_buffer_range_EXT)(CGL_MACRO_CONTEXT_RENDERER, target, index, buffer, offset, size)

#define glBindBufferBase(target, index, buffer) \
    (*(CGL_MACRO_CONTEXT)->disp.bind_buffer_base_EXT)(CGL_MACRO_CONTEXT_RENDERER, target, index, buffer)

#define glTransformFeedbackVaryings(program, count, varyings, bufferMode) \
    (*(CGL_MACRO_CONTEXT)->disp.transform_feedback_varyings_EXT)(CGL_MACRO_CONTEXT_RENDERER, program, count, varyings, bufferMode)

#define glGetTransformFeedbackVarying(program, index, bufSize, length, size, type, name) \
    (*(CGL_MACRO_CONTEXT)->disp.get_transform_feedback_varying_EXT)(CGL_MACRO_CONTEXT_RENDERER, program, index, bufSize, length, size, type, name)

#define glClampColor(target, clamp) \
    (*(CGL_MACRO_CONTEXT)->disp.clamp_color_ARB)(CGL_MACRO_CONTEXT_RENDERER, target, clamp)

#define glBeginConditionalRender(id, mode) \
    (*(CGL_MACRO_CONTEXT)->disp.begin_conditional_render_NV)(CGL_MACRO_CONTEXT_RENDERER, id, mode)

#define glEndConditionalRender() \
    (*(CGL_MACRO_CONTEXT)->disp.end_conditional_render_NV)(CGL_MACRO_CONTEXT_RENDERER)

#define glVertexAttribIPointer(index, size, type, stride, pointer) \
    (*(CGL_MACRO_CONTEXT)->disp.vertex_attribI_pointer_EXT)(CGL_MACRO_CONTEXT_RENDERER, index, size, type, stride, pointer)

#define glGetVertexAttribIiv(index, pname, params) \
    (*(CGL_MACRO_CONTEXT)->disp.get_vertex_attribIiv_EXT)(CGL_MACRO_CONTEXT_RENDERER, index, pname, params)

#define glGetVertexAttribIuiv(index, pname, params) \
    (*(CGL_MACRO_CONTEXT)->disp.get_vertex_attribIuiv_EXT)(CGL_MACRO_CONTEXT_RENDERER, index, pname, params)

#define glVertexAttribI1i(index, x) \
    (*(CGL_MACRO_CONTEXT)->disp.vertex_attribI1i_EXT)(CGL_MACRO_CONTEXT_RENDERER, index, x)

#define glVertexAttribI2i(index, x, y) \
    (*(CGL_MACRO_CONTEXT)->disp.vertex_attribI2i_EXT)(CGL_MACRO_CONTEXT_RENDERER, index, x, y)

#define glVertexAttribI3i(index, x, y, z) \
    (*(CGL_MACRO_CONTEXT)->disp.vertex_attribI3i_EXT)(CGL_MACRO_CONTEXT_RENDERER, index, x, y, z)

#define glVertexAttribI4i(index, x, y, z, w) \
    (*(CGL_MACRO_CONTEXT)->disp.vertex_attribI4i_EXT)(CGL_MACRO_CONTEXT_RENDERER, index, x, y, z, w)

#define glVertexAttribI1ui(index, x) \
    (*(CGL_MACRO_CONTEXT)->disp.vertex_attribI1ui_EXT)(CGL_MACRO_CONTEXT_RENDERER, index, x)

#define glVertexAttribI2ui(index, x, y) \
    (*(CGL_MACRO_CONTEXT)->disp.vertex_attribI2ui_EXT)(CGL_MACRO_CONTEXT_RENDERER, index, x, y)

#define glVertexAttribI3ui(index, x, y, z) \
    (*(CGL_MACRO_CONTEXT)->disp.vertex_attribI3ui_EXT)(CGL_MACRO_CONTEXT_RENDERER, index, x, y, z)

#define glVertexAttribI4ui(index, x, y, z, w) \
    (*(CGL_MACRO_CONTEXT)->disp.vertex_attribI4ui_EXT)(CGL_MACRO_CONTEXT_RENDERER, index, x, y, z, w)

#define glVertexAttribI1iv(index, v) \
    (*(CGL_MACRO_CONTEXT)->disp.vertex_attribI1iv_EXT)(CGL_MACRO_CONTEXT_RENDERER, index, v)

#define glVertexAttribI2iv(index, v) \
    (*(CGL_MACRO_CONTEXT)->disp.vertex_attribI2iv_EXT)(CGL_MACRO_CONTEXT_RENDERER, index, v)

#define glVertexAttribI3iv(index, v) \
    (*(CGL_MACRO_CONTEXT)->disp.vertex_attribI3iv_EXT)(CGL_MACRO_CONTEXT_RENDERER, index, v)

#define glVertexAttribI4iv(index, v) \
    (*(CGL_MACRO_CONTEXT)->disp.vertex_attribI4iv_EXT)(CGL_MACRO_CONTEXT_RENDERER, index, v)

#define glVertexAttribI1uiv(index, v) \
    (*(CGL_MACRO_CONTEXT)->disp.vertex_attribI1uiv_EXT)(CGL_MACRO_CONTEXT_RENDERER, index, v)

#define glVertexAttribI2uiv(index, v) \
    (*(CGL_MACRO_CONTEXT)->disp.vertex_attribI2uiv_EXT)(CGL_MACRO_CONTEXT_RENDERER, index, v)

#define glVertexAttribI3uiv(index, v) \
    (*(CGL_MACRO_CONTEXT)->disp.vertex_attribI3uiv_EXT)(CGL_MACRO_CONTEXT_RENDERER, index, v)

#define glVertexAttribI4uiv(index, v) \
    (*(CGL_MACRO_CONTEXT)->disp.vertex_attribI4uiv_EXT)(CGL_MACRO_CONTEXT_RENDERER, index, v)

#define glVertexAttribI4bv(index, v) \
    (*(CGL_MACRO_CONTEXT)->disp.vertex_attribI4bv_EXT)(CGL_MACRO_CONTEXT_RENDERER, index, v)

#define glVertexAttribI4sv(index, v) \
    (*(CGL_MACRO_CONTEXT)->disp.vertex_attribI4sv_EXT)(CGL_MACRO_CONTEXT_RENDERER, index, v)

#define glVertexAttribI4ubv(index, v) \
    (*(CGL_MACRO_CONTEXT)->disp.vertex_attribI4ubv_EXT)(CGL_MACRO_CONTEXT_RENDERER, index, v)

#define glVertexAttribI4usv(index, v) \
    (*(CGL_MACRO_CONTEXT)->disp.vertex_attribI4usv_EXT)(CGL_MACRO_CONTEXT_RENDERER, index, v)

#define glGetUniformuiv(program, location, params) \
    (*(CGL_MACRO_CONTEXT)->disp.get_uniformuiv_EXT)(CGL_MACRO_CONTEXT_RENDERER, program, location, params)

#define glBindFragDataLocation(program, color, name) \
    (*(CGL_MACRO_CONTEXT)->disp.bind_frag_data_location_EXT)(CGL_MACRO_CONTEXT_RENDERER, program, color, name)

#define glGetFragDataLocation(program, name) \
    (*(CGL_MACRO_CONTEXT)->disp.get_frag_data_location_EXT)(CGL_MACRO_CONTEXT_RENDERER, program, name)

#define glUniform1ui(location, v0) \
    (*(CGL_MACRO_CONTEXT)->disp.uniform1ui_EXT)(CGL_MACRO_CONTEXT_RENDERER, location, v0)

#define glUniform2ui(location, v0, v1) \
    (*(CGL_MACRO_CONTEXT)->disp.uniform2ui_EXT)(CGL_MACRO_CONTEXT_RENDERER, location, v0, v1)

#define glUniform3ui(location, v0, v1, v2) \
    (*(CGL_MACRO_CONTEXT)->disp.uniform3ui_EXT)(CGL_MACRO_CONTEXT_RENDERER, location, v0, v1, v2)

#define glUniform4ui(location, v0, v1, v2, v3) \
    (*(CGL_MACRO_CONTEXT)->disp.uniform4ui_EXT)(CGL_MACRO_CONTEXT_RENDERER, location, v0, v1, v2, v3)

#define glUniform1uiv(location, count, value) \
    (*(CGL_MACRO_CONTEXT)->disp.uniform1uiv_EXT)(CGL_MACRO_CONTEXT_RENDERER, location, count, value)

#define glUniform2uiv(location, count, value) \
    (*(CGL_MACRO_CONTEXT)->disp.uniform2uiv_EXT)(CGL_MACRO_CONTEXT_RENDERER, location, count, value)

#define glUniform3uiv(location, count, value) \
    (*(CGL_MACRO_CONTEXT)->disp.uniform3uiv_EXT)(CGL_MACRO_CONTEXT_RENDERER, location, count, value)

#define glUniform4uiv(location, count, value) \
    (*(CGL_MACRO_CONTEXT)->disp.uniform4uiv_EXT)(CGL_MACRO_CONTEXT_RENDERER, location, count, value)

#define glTexParameterIiv(target, pname, params) \
    (*(CGL_MACRO_CONTEXT)->disp.tex_parameterIiv_EXT)(CGL_MACRO_CONTEXT_RENDERER, target, pname, params)

#define glTexParameterIuiv(target, pname, params) \
    (*(CGL_MACRO_CONTEXT)->disp.tex_parameterIuiv_EXT)(CGL_MACRO_CONTEXT_RENDERER, target, pname, params)

#define glGetTexParameterIiv(target, pname, params) \
    (*(CGL_MACRO_CONTEXT)->disp.get_tex_parameterIiv_EXT)(CGL_MACRO_CONTEXT_RENDERER, target, pname, params)

#define glGetTexParameterIuiv(target, pname, params) \
    (*(CGL_MACRO_CONTEXT)->disp.get_tex_parameterIuiv_EXT)(CGL_MACRO_CONTEXT_RENDERER, target, pname, params)

#define glClearBufferiv(buffer, drawbuffer, value) \
    (*(CGL_MACRO_CONTEXT)->disp.clear_bufferiv)(CGL_MACRO_CONTEXT_RENDERER, buffer, drawbuffer, value)

#define glClearBufferuiv(buffer, drawbuffer, value) \
    (*(CGL_MACRO_CONTEXT)->disp.clear_bufferuiv)(CGL_MACRO_CONTEXT_RENDERER, buffer, drawbuffer, value)

#define glClearBufferfv(buffer, drawbuffer, value) \
    (*(CGL_MACRO_CONTEXT)->disp.clear_bufferfv)(CGL_MACRO_CONTEXT_RENDERER, buffer, drawbuffer, value)

#define glClearBufferfi(buffer, drawbuffer, depth, stencil) \
    (*(CGL_MACRO_CONTEXT)->disp.clear_bufferfi)(CGL_MACRO_CONTEXT_RENDERER, buffer, drawbuffer, depth, stencil)

#define glGetStringi(name, index) \
    (*(CGL_MACRO_CONTEXT)->disp.get_stringi)(CGL_MACRO_CONTEXT_RENDERER, name, index)

#define glDrawArraysInstanced(mode, first, count, primcount) \
    (*(CGL_MACRO_CONTEXT)->disp.draw_arrays_instanced)(CGL_MACRO_CONTEXT_RENDERER, mode, first, count, primcount)

#define glDrawElementsInstanced(mode, count, type, indices, primcount) \
    (*(CGL_MACRO_CONTEXT)->disp.draw_elements_instanced)(CGL_MACRO_CONTEXT_RENDERER, mode, count, type, indices, primcount)

#define glTexBuffer(target, internalformat, buffer) \
    (*(CGL_MACRO_CONTEXT)->disp.tex_buffer)(CGL_MACRO_CONTEXT_RENDERER, target, internalformat, buffer)

#define glPrimitiveRestartIndex(index) \
    (*(CGL_MACRO_CONTEXT)->disp.primitive_restart_index)(CGL_MACRO_CONTEXT_RENDERER, index)

#define glGetInteger64i_v(target, index, data) \
    (*(CGL_MACRO_CONTEXT)->disp.get_integer64i_v)(CGL_MACRO_CONTEXT_RENDERER, target, index, data)

#define glGetBufferParameteri64v(target, pname, params) \
    (*(CGL_MACRO_CONTEXT)->disp.get_buffer_parameteri64v)(CGL_MACRO_CONTEXT_RENDERER, target, pname, params)

#define glFramebufferTexture(target, attachment, texture, level) \
    (*(CGL_MACRO_CONTEXT)->disp.framebuffer_texture_EXT)(CGL_MACRO_CONTEXT_RENDERER, target, attachment, texture, level)

#define glIsRenderbuffer(renderbuffer) \
    (*(CGL_MACRO_CONTEXT)->disp.is_renderbuffer_EXT)(CGL_MACRO_CONTEXT_RENDERER, renderbuffer)

#define glBindRenderbuffer(target, renderbuffer) \
    (*(CGL_MACRO_CONTEXT)->disp.bind_renderbuffer_EXT)(CGL_MACRO_CONTEXT_RENDERER, target, renderbuffer)

#define glDeleteRenderbuffers(n, renderbuffers) \
    (*(CGL_MACRO_CONTEXT)->disp.delete_renderbuffers_EXT)(CGL_MACRO_CONTEXT_RENDERER, n, renderbuffers)

#define glGenRenderbuffers(n, renderbuffers) \
    (*(CGL_MACRO_CONTEXT)->disp.gen_renderbuffers_EXT)(CGL_MACRO_CONTEXT_RENDERER, n, renderbuffers)

#define glRenderbufferStorage(target, internalformat, width, height) \
    (*(CGL_MACRO_CONTEXT)->disp.renderbuffer_storage_EXT)(CGL_MACRO_CONTEXT_RENDERER, target, internalformat, width, height)

#define glGetRenderbufferParameteriv(target, pname, params) \
    (*(CGL_MACRO_CONTEXT)->disp.get_renderbuffer_parameteriv_EXT)(CGL_MACRO_CONTEXT_RENDERER, target, pname, params)

#define glIsFramebuffer(framebuffer) \
    (*(CGL_MACRO_CONTEXT)->disp.is_framebuffer_EXT)(CGL_MACRO_CONTEXT_RENDERER, framebuffer)

#define glBindFramebuffer(target, framebuffer) \
    (*(CGL_MACRO_CONTEXT)->disp.bind_framebuffer_EXT)(CGL_MACRO_CONTEXT_RENDERER, target, framebuffer)

#define glDeleteFramebuffers(n, framebuffers) \
    (*(CGL_MACRO_CONTEXT)->disp.delete_framebuffers_EXT)(CGL_MACRO_CONTEXT_RENDERER, n, framebuffers)

#define glGenFramebuffers(n, framebuffers) \
    (*(CGL_MACRO_CONTEXT)->disp.gen_framebuffers_EXT)(CGL_MACRO_CONTEXT_RENDERER, n, framebuffers)

#define glCheckFramebufferStatus(target) \
    (*(CGL_MACRO_CONTEXT)->disp.check_framebuffer_status_EXT)(CGL_MACRO_CONTEXT_RENDERER, target)

#define glFramebufferTexture1D(target, attachment, textarget, texture, level) \
    (*(CGL_MACRO_CONTEXT)->disp.framebuffer_texture1D_EXT)(CGL_MACRO_CONTEXT_RENDERER, target, attachment, textarget, texture, level)

#define glFramebufferTexture2D(target, attachment, textarget, texture, level) \
    (*(CGL_MACRO_CONTEXT)->disp.framebuffer_texture2D_EXT)(CGL_MACRO_CONTEXT_RENDERER, target, attachment, textarget, texture, level)

#define glFramebufferTexture3D(target, attachment, textarget, texture, level, zoffset) \
    (*(CGL_MACRO_CONTEXT)->disp.framebuffer_texture3D_EXT)(CGL_MACRO_CONTEXT_RENDERER, target, attachment, textarget, texture, level, zoffset)

#define glFramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer) \
    (*(CGL_MACRO_CONTEXT)->disp.framebuffer_renderbuffer_EXT)(CGL_MACRO_CONTEXT_RENDERER, target, attachment, renderbuffertarget, renderbuffer)

#define glGetFramebufferAttachmentParameteriv(target, attachment, pname, params) \
    (*(CGL_MACRO_CONTEXT)->disp.get_framebuffer_attachment_parameteriv_EXT)(CGL_MACRO_CONTEXT_RENDERER, target, attachment, pname, params)

#define glGenerateMipmap(target) \
    (*(CGL_MACRO_CONTEXT)->disp.generate_mipmap_EXT)(CGL_MACRO_CONTEXT_RENDERER, target)

#define glBlitFramebuffer(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter) \
    (*(CGL_MACRO_CONTEXT)->disp.blit_framebuffer_EXT)(CGL_MACRO_CONTEXT_RENDERER, srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter)

#define glRenderbufferStorageMultisample(target, samples, internalformat, width, height) \
    (*(CGL_MACRO_CONTEXT)->disp.renderbuffer_storage_multisample_EXT)(CGL_MACRO_CONTEXT_RENDERER, target, samples, internalformat, width, height)

#define glFramebufferTextureLayer(target, attachment, texture, level, layer) \
    (*(CGL_MACRO_CONTEXT)->disp.framebuffer_texture_layer_EXT)(CGL_MACRO_CONTEXT_RENDERER, target, attachment, texture, level, layer)

#define glMapBufferRange(target, offset, length, access) \
    (*(CGL_MACRO_CONTEXT)->disp.map_buffer_range)(CGL_MACRO_CONTEXT_RENDERER, target, offset, length, access)

#define glFlushMappedBufferRange(target, offset, length) \
    (*(CGL_MACRO_CONTEXT)->disp.flush_mapped_buffer_range)(CGL_MACRO_CONTEXT_RENDERER, target, offset, length)

#define glBindVertexArray(array) \
    (*(CGL_MACRO_CONTEXT)->disp.bind_vertex_array_ARB)(CGL_MACRO_CONTEXT_RENDERER, array)

#define glDeleteVertexArrays(n, arrays) \
    (*(CGL_MACRO_CONTEXT)->disp.delete_vertex_arrays_ARB)(CGL_MACRO_CONTEXT_RENDERER, n, arrays)

#define glGenVertexArrays(n, arrays) \
    (*(CGL_MACRO_CONTEXT)->disp.gen_vertex_arrays_ARB)(CGL_MACRO_CONTEXT_RENDERER, n, arrays)

#define glIsVertexArray(array) \
    (*(CGL_MACRO_CONTEXT)->disp.is_vertex_array_ARB)(CGL_MACRO_CONTEXT_RENDERER, array)

#define glGetUniformIndices(program, uniformCount, uniformNames, uniformIndices) \
    (*(CGL_MACRO_CONTEXT)->disp.get_uniform_indices)(CGL_MACRO_CONTEXT_RENDERER, program, uniformCount, uniformNames, uniformIndices)

#define glGetActiveUniformsiv(program, uniformCount, uniformIndices, pname, params) \
    (*(CGL_MACRO_CONTEXT)->disp.get_active_uniformsiv)(CGL_MACRO_CONTEXT_RENDERER, program, uniformCount, uniformIndices, pname, params)

#define glGetActiveUniformName(program, uniformIndex, bufSize, length, uniformName) \
    (*(CGL_MACRO_CONTEXT)->disp.get_active_uniform_name)(CGL_MACRO_CONTEXT_RENDERER, program, uniformIndex, bufSize, length, uniformName)

#define glGetUniformBlockIndex(program, uniformBlockName) \
    (*(CGL_MACRO_CONTEXT)->disp.get_uniform_block_index)(CGL_MACRO_CONTEXT_RENDERER, program, uniformBlockName)

#define glGetActiveUniformBlockiv(program, uniformBlockIndex, pname, params) \
    (*(CGL_MACRO_CONTEXT)->disp.get_active_uniform_blockiv)(CGL_MACRO_CONTEXT_RENDERER, program, uniformBlockIndex, pname, params)

#define glGetActiveUniformBlockName(program, uniformBlockIndex, bufSize, length, uniformBlockName) \
    (*(CGL_MACRO_CONTEXT)->disp.get_active_uniform_block_name)(CGL_MACRO_CONTEXT_RENDERER, program, uniformBlockIndex, bufSize, length, uniformBlockName)

#define glUniformBlockBinding(program, uniformBlockIndex, uniformBlockBinding) \
    (*(CGL_MACRO_CONTEXT)->disp.uniform_block_binding)(CGL_MACRO_CONTEXT_RENDERER, program, uniformBlockIndex, uniformBlockBinding)

#define glCopyBufferSubData(readTarget, writeTarget, readOffset, writeOffset, size) \
    (*(CGL_MACRO_CONTEXT)->disp.copy_buffer_sub_data)(CGL_MACRO_CONTEXT_RENDERER, readTarget, writeTarget, readOffset, writeOffset, size)

#define glDrawElementsBaseVertex(mode, count, type, indices, basevertex) \
    (*(CGL_MACRO_CONTEXT)->disp.draw_elements_base_vertex)(CGL_MACRO_CONTEXT_RENDERER, mode, count, type, indices, basevertex)

#define glDrawRangeElementsBaseVertex(mode, start, end, count, type, indices, basevertex) \
    (*(CGL_MACRO_CONTEXT)->disp.draw_range_elements_base_vertex)(CGL_MACRO_CONTEXT_RENDERER, mode, start, end, count, type, indices, basevertex)

#define glDrawElementsInstancedBaseVertex(mode, count, type, indices, primcount, basevertex) \
    (*(CGL_MACRO_CONTEXT)->disp.draw_elements_instanced_base_vertex)(CGL_MACRO_CONTEXT_RENDERER, mode, count, type, indices, primcount, basevertex)

#define glMultiDrawElementsBaseVertex(mode, count, type, indices, primcount, basevertex) \
    (*(CGL_MACRO_CONTEXT)->disp.multi_draw_elements_base_vertex)(CGL_MACRO_CONTEXT_RENDERER, mode, count, type, indices, primcount, basevertex)

#define glProvokingVertex(mode) \
    (*(CGL_MACRO_CONTEXT)->disp.provoking_vertex_EXT)(CGL_MACRO_CONTEXT_RENDERER, mode)

#define glFenceSync(condition, flags) \
    (*(CGL_MACRO_CONTEXT)->disp.fence_sync)(CGL_MACRO_CONTEXT_RENDERER, condition, flags)

#define glIsSync(sync) \
    (*(CGL_MACRO_CONTEXT)->disp.is_sync)(CGL_MACRO_CONTEXT_RENDERER, sync)

#define glDeleteSync(sync) \
    (*(CGL_MACRO_CONTEXT)->disp.delete_sync)(CGL_MACRO_CONTEXT_RENDERER, sync)

#define glClientWaitSync(sync, flags, timeout) \
    (*(CGL_MACRO_CONTEXT)->disp.client_wait_sync)(CGL_MACRO_CONTEXT_RENDERER, sync, flags, timeout)

#define glWaitSync(sync, flags, timeout) \
    (*(CGL_MACRO_CONTEXT)->disp.wait_sync)(CGL_MACRO_CONTEXT_RENDERER, sync, flags, timeout)

#define glGetInteger64v(pname, params) \
    (*(CGL_MACRO_CONTEXT)->disp.get_integer64v_sync)(CGL_MACRO_CONTEXT_RENDERER, pname, params)

#define glGetSynciv(sync, pname, bufSize, length, values) \
    (*(CGL_MACRO_CONTEXT)->disp.get_synciv)(CGL_MACRO_CONTEXT_RENDERER, sync, pname, bufSize, length, values)

#define glTexImage2DMultisample(target, samples, internalformat, width, height, fixedsamplelocations) \
    (*(CGL_MACRO_CONTEXT)->disp.tex_image2D_multisample)(CGL_MACRO_CONTEXT_RENDERER, target, samples, internalformat, width, height, fixedsamplelocations)

#define glTexImage3DMultisample(target, samples, internalformat, width, height, depth, fixedsamplelocations) \
    (*(CGL_MACRO_CONTEXT)->disp.tex_image3D_multisample)(CGL_MACRO_CONTEXT_RENDERER, target, samples, internalformat, width, height, depth, fixedsamplelocations)

#define glGetMultisamplefv(pname, index, val) \
    (*(CGL_MACRO_CONTEXT)->disp.get_multisamplefv)(CGL_MACRO_CONTEXT_RENDERER, pname, index, val)

#define glSampleMaski(index, mask) \
    (*(CGL_MACRO_CONTEXT)->disp.sample_maski)(CGL_MACRO_CONTEXT_RENDERER, index, mask)

#define glVertexAttribDivisorARB(index, divisor) \
    (*(CGL_MACRO_CONTEXT)->disp.vertex_attrib_divisor)(CGL_MACRO_CONTEXT_RENDERER, index, divisor)

#define glGenSamplers(count, samplers) \
    (*(CGL_MACRO_CONTEXT)->disp.gen_samplers)(CGL_MACRO_CONTEXT_RENDERER, count, samplers)

#define glDeleteSamplers(count, samplers) \
    (*(CGL_MACRO_CONTEXT)->disp.delete_samplers)(CGL_MACRO_CONTEXT_RENDERER, count, samplers)

#define glIsSampler(sampler) \
    (*(CGL_MACRO_CONTEXT)->disp.is_sampler)(CGL_MACRO_CONTEXT_RENDERER, sampler)

#define glBindSampler(unit, sampler) \
    (*(CGL_MACRO_CONTEXT)->disp.bind_sampler)(CGL_MACRO_CONTEXT_RENDERER, unit, sampler)

#define glSamplerParameteri(sampler, pname, param) \
    (*(CGL_MACRO_CONTEXT)->disp.sampler_parameteri)(CGL_MACRO_CONTEXT_RENDERER, sampler, pname, param)

#define glSamplerParameteriv(sampler, pname, param) \
    (*(CGL_MACRO_CONTEXT)->disp.sampler_parameteriv)(CGL_MACRO_CONTEXT_RENDERER, sampler, pname, param)

#define glSamplerParameterf(sampler, pname, param) \
    (*(CGL_MACRO_CONTEXT)->disp.sampler_parameterf)(CGL_MACRO_CONTEXT_RENDERER, sampler, pname, param)

#define glSamplerParameterfv(sampler, pname, param) \
    (*(CGL_MACRO_CONTEXT)->disp.sampler_parameterfv)(CGL_MACRO_CONTEXT_RENDERER, sampler, pname, param)

#define glSamplerParameterIiv(sampler, pname, param) \
    (*(CGL_MACRO_CONTEXT)->disp.sampler_parameterIiv)(CGL_MACRO_CONTEXT_RENDERER, sampler, pname, param)

#define glSamplerParameterIuiv(sampler, pname, param) \
    (*(CGL_MACRO_CONTEXT)->disp.sampler_parameterIuiv)(CGL_MACRO_CONTEXT_RENDERER, sampler, pname, param)

#define glGetSamplerParameteriv(sampler, pname, params) \
    (*(CGL_MACRO_CONTEXT)->disp.get_sampler_parameteriv)(CGL_MACRO_CONTEXT_RENDERER, sampler, pname, params)

#define glGetSamplerParameterfv(sampler, pname, params) \
    (*(CGL_MACRO_CONTEXT)->disp.get_sampler_parameterfv)(CGL_MACRO_CONTEXT_RENDERER, sampler, pname, params)

#define glGetSamplerParameterIiv(sampler, pname, params) \
    (*(CGL_MACRO_CONTEXT)->disp.get_sampler_parameterIiv)(CGL_MACRO_CONTEXT_RENDERER, sampler, pname, params)

#define glGetSamplerParameterIuiv(sampler, pname, params) \
    (*(CGL_MACRO_CONTEXT)->disp.get_sampler_parameterIuiv)(CGL_MACRO_CONTEXT_RENDERER, sampler, pname, params)

#define glQueryCounter(id, target) \
    (*(CGL_MACRO_CONTEXT)->disp.query_counter)(CGL_MACRO_CONTEXT_RENDERER, id, target)

#define glGetQueryObjecti64v(id, pname, params) \
    (*(CGL_MACRO_CONTEXT)->disp.get_query_objecti64v)(CGL_MACRO_CONTEXT_RENDERER, id, pname, params)

#define glGetQueryObjectui64v(id, pname, params) \
    (*(CGL_MACRO_CONTEXT)->disp.get_query_objectui64v)(CGL_MACRO_CONTEXT_RENDERER, id, pname, params)

#define glObjectPurgeableAPPLE(objectType, name, option) \
    (*(CGL_MACRO_CONTEXT)->disp.object_purgeable_APPLE)(CGL_MACRO_CONTEXT_RENDERER, objectType, name, option)

#define glObjectUnpurgeableAPPLE(objectType, name, option) \
    (*(CGL_MACRO_CONTEXT)->disp.object_unpurgeable_APPLE)(CGL_MACRO_CONTEXT_RENDERER, objectType, name, option)

#define glGetObjectParameterivAPPLE(objectType, name, pname, params) \
    (*(CGL_MACRO_CONTEXT)->disp.get_object_parameteriv_APPLE)(CGL_MACRO_CONTEXT_RENDERER, objectType, name, pname, params)

#define glTextureRangeAPPLE(target, length, pointer) \
    (*(CGL_MACRO_CONTEXT)->disp.texture_range_APPLE)(CGL_MACRO_CONTEXT_RENDERER, target, length, pointer)

#define glGetTexParameterPointervAPPLE(target, pname, params) \
    (*(CGL_MACRO_CONTEXT)->disp.get_tex_parameter_pointerv_APPLE)(CGL_MACRO_CONTEXT_RENDERER, target, pname, params)

#endif /* _CGL3MACRO_H */
