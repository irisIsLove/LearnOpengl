#version 330 core
layout(location = 0) in vec3 a_pos;
layout(location = 1) in vec3 a_color;

out vec3 out_pos;

void
main()
{
  gl_Position = vec4(a_pos.x, a_pos.y, a_pos.z, 1.0);
  out_pos = a_pos;
}
