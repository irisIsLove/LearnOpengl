#version 330 core
in vec3 out_pos;
out vec4 frag_color;

void
main()
{
  frag_color = vec4(out_pos, 1.0);
}
