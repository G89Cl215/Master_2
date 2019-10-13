/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   karatsuba.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 10:04:59 by tgouedar          #+#    #+#             */
/*   Updated: 2019/10/13 10:11:03 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdio.h>

size_t  ln_2(unsigned long a)
{
    unsigned long    len;
    unsigned long    size;

    len = 1;
    size = 8 * sizeof(long) - 1;
    len <<= size;
    while (!(len & a))
    {
        len >>= 1;
        size--;
    }
    return (size - 1);
}

/*                                                                            */
/* Algorithme de multiplication rapide de complexite moindre que l'algo naif  */
/*                                                                            */

unsigned long     karatsuba(long a, long b, size_t k)
{
    long    a1;
    long    a2;
    long    b1;
    long    b2;
    long    c;

    if (!a || !b)
        return (0);
    if (k <= 4)
        return (a * b);
    a1 = a >> (k >> 1);
    b1 = b >> (k >> 1);
    a2 = a ^ (a1 << (k >> 1));
    b2 = b ^ (b1 << (k >> 1));
    a = karatsuba(a1, b1, k >> 1);
    b = karatsuba(a2, b2, k >> 1);
    c = karatsuba(a1 - a2, b1 - b2, k >> 1);
    return ((a << k) + ((a + b - c) << (k >> 1)) + b);
}

//int main(void)
//{
//    long     a;
//    long     b;
//    size_t   c;
//
//    a = 9876;
//    b = 98761;
//    c = ln_2(a | b);
//    a = karatsuba(a, b, c);
//    printf("resultat de Karatsuba : %li\n", a);
//    return (0);
//}
