G = tf([-5.428 8.30484],[1 0.1339 54.1]);
[num,den] = tfdata(G,'v');
[A,B,C,D] = tf2ss(num,den);

a1 = input('Penalización error x1: ');
b1 = input('Penalización error x2: ');
c1 = input('Penalización geneRal esfuerzo del actuador: ');
nombreStep = strcat('Step-',replace(string(a1),'.',','),'-',replace(string(b1),'.',','),'-',replace(string(c1),'.',','));
nombreRlocus = strcat('Rlocus-',replace(string(a1),'.',','),'-',replace(string(b1),'.',','),'-',replace(string(c1),'.',','));

Q = [a1 0;0 b1];
K = lqr(A,B,Q,c1);
sys = ss((A-B*K),B,C,D);
[A1,B1,C1,D1] = ssdata(sys);

[n,d] = ss2tf(A1,B1,C1,D1);
G1 = tf(n,d);

figure(1);
step(G1)
saveas(figure(1),nombreStep,'jpeg');
fprintf('%s guardada!\n',nombreStep);

figure(2);
rlocus(G1)
saveas(figure(2),nombreRlocus,'jpeg');
fprintf('%s guardada!\n',nombreRlocus);