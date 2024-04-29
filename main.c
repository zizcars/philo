/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Achakkaf <zizcarschak1@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:01:09 by Achakkaf          #+#    #+#             */
/*   Updated: 2024/04/29 12:35:09 by Achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pholi.h"

int main()
{
    struct timeval time1;
    struct timeval time2;
    gettimeofday(&time1, NULL);
    usleep(1000000);
    gettimeofday(&time2, NULL);
    printf("TIME:%d\n",time2.tv_sec - time1.tv_sec);
}