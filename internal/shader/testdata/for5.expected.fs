uniform float U0;
uniform float U1;
uniform float U2;

int F0(in int l0);

int F0(in int l0) {
	return l0;
}

void main(void) {
	int l0 = 0;
	int l2 = 0;
	l0 = 0;
	for (int l1 = 0; l1 < 10; l1++) {
		int l2 = 0;
		int l3 = 0;
		l2 = F0(l1);
		l3 = l2;
		l0 = (l0) + (l3);
		for (int l4 = 0; l4 < 10; l4++) {
			int l5 = 0;
			int l6 = 0;
			l5 = F0(l4);
			l6 = l5;
			l0 = (l0) + (l6);
		}
	}
	l2 = 0;
	l0 = (l0) + (l2);
	gl_FragColor = vec4(l0);
	return;
}
