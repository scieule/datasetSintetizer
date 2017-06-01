# @Author: Rafael H. Tibaes <rafael>
# @Date:   2017-06-01T10:35:43-03:00
# @Email:  r@fael.nl
# @Project: Biometrics Research
# @Filename: Makefile
# @Last modified by:   rafael
# @Last modified time: 2017-06-01T10:36:40-03:00
# @License: MIT
# @Copyright: Nandlands and Akiyama



CXX = g++
CXXFLAGS = -O3 --std=c++14 -Wall `pkg-config --cflags --libs opencv`
