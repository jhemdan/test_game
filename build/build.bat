set cl_includes=/IC:/dev/_lib15/sdl/include/ /IC:/dev/_lib15/glew/include/ /IC:/dev/_lib15/vecmath/include/
set src_dir=../src/
set cl_srcs=%src_dir%main.cpp %src_dir%log.cpp %src_dir%exception.cpp %src_dir%bitmap.cpp %src_dir%texture2d.cpp %src_dir%shader.cpp %src_dir%mesh.cpp %src_dir%model.cpp

cl /c %cl_includes% %cl_srcs%

set lib_dirs=/LIBPATH:C:/dev/_lib15/sdl/lib/ /LIBPATH:C:/dev/_lib15/glew/lib/ /LIBPATH:C:/dev/_lib15/vecmath/lib/
set libs=SDL2.lib SDL2main.lib SDL2_image.lib opengl32.lib glew32.lib vecmath.lib
set objs=main.obj log.obj exception.obj bitmap.obj texture2d.obj shader.obj mesh.obj model.obj

link /SUBSYSTEM:CONSOLE %lib_dirs% %libs% %objs%