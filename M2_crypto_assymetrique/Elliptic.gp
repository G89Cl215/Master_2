potx(m)={vector(K, j, Mod(m*K+j, mod));}
ft_ec(x)={Mod(x^3-x+188, mod);}
code(m)=
{
	i=1;
	pot_x = potx(m);
	for(i=1,20,
		y=ft_ec(pot_x[i]);
		print(lift(y),"   ", lift(pot_x[i]));
		if(kronecker(lift(y), mod)==1, return([lift(pot_x[i]),lift(y)]);));
}


mod=751;
K=20;
