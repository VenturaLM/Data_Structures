#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sun Mar 29 13:16:42 2020

@author: ma1macuf
"""

import numpy as np


def generate_pull_of_directions(num):
    '''Generate a random pull of ipv4 directions.'''
    return np.random.randint(1, 256, size=(num, 4))


def generate_weighted_wheel(pull, max_weight):
    '''Generate a wheel to pickup at random with weights.'''
    weigths = np.random.randint(max_weight, size=pull.shape[0])
    wheel = None
    for i in range(pull.shape[0]):
        for j in range(weigths[i]):
            if wheel is None:
                wheel = pull[i]
            else:
                wheel = np.vstack((wheel, pull[i]))
    return wheel


def generate_test_case(num_ips=1000, max_ip_weight=10,
                       n_connections_per_second=2.0, seconds=3600):
    wheel = generate_weighted_wheel(generate_pull_of_directions(num_ips),
                                    max_ip_weight)
    # We want 2 connections per second, 3600 seconds.
    n_connections = np.random.poisson(lam=n_connections_per_second,
                                      size=seconds)
    for i in range(seconds):
        if n_connections[i] > 0:
            ips = np.random.randint(wheel.shape[0], size=n_connections[i])
            for j in range(n_connections[i]):
                ip = wheel[ips[j]]
                print('{} {}.{}.{}.{}'.format(i, ip[0], ip[1], ip[2], ip[3]))
                

if __name__==   '__main__':
    np.random.seed(seed=None)
    generate_test_case()
