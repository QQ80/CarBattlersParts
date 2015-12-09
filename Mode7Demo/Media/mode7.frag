uniform vec2 resolution;
uniform vec2 offset;
uniform float scaling;
uniform float fov;
uniform float angle;
uniform sampler2D texture;

void main()
{
	vec2 pos = ( gl_FragCoord.xy / resolution.xy ) - vec2(0.5,0.5);

	vec3 p = vec3(pos.x, fov, pos.y - 0.75f);
	vec2 s = vec2(p.x/p.z, p.y/p.z) * scaling;

	// Add offset
    vec2 a = vec2(s.x + offset.x, s.y + offset.y);

	// Rotate View
	vec2 r = vec2(a.x * cos(angle) - a.y * sin(angle) , a.x * sin(angle) + a.y * cos(angle));

	vec4 color = texture2D(texture, vec2(-r.x, r.y));
	//fadingcolor *= p.z*p.z*10.0;

	gl_FragColor = vec4( color );
}
