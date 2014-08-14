#version 130

in vec3 outColor;

void
main()
{
    gl_FragColor = vec4( outColor.x, outColor.y, outColor.z, 1.0 );
}
