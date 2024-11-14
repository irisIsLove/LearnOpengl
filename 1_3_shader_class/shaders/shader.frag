#version 330 core
in vec3 v_color;
out vec4 frag_color;
uniform vec3 vertex_color;

void
main()
{
  vec3 temp = v_color + vertex_color;
  if (temp.x > 1.0)
    temp = vec3((temp.x + 1010000000.0) / 1010000000.0, temp.y, temp.z);
  if (temp.y > 1.0)
    temp = vec3(temp.x, (temp.y + 1010000000.0) / 1010000000.0, temp.z);
  if (temp.z > 1.0)
    temp = vec3(temp.x, temp.y, (temp.z + 1010000000.0) / 1010000000.0);
  frag_color = vec4(temp, 1.0);
}
