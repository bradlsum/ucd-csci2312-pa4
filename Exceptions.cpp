//
// Created by Sumner Bradley on 4/12/2016.
//

#include <iostream>
#include "Exceptions.h"

using namespace Gaming;

void GamingException::setName(std::string name) { __name = name; }

std::ostream &operator<<(std::ostream &os, const GamingException &ex) {

    os << ex.getName() << std::endl;

    ex.__print_args(os);

    return os;

}

DimensionEx::DimensionEx(unsigned expWidth, unsigned expHeight, unsigned width, unsigned height) {

    __exp_height = expHeight;
    __exp_width = expWidth;

    __height = height;
    __width = width;

    setName("DimensionEx");

}

unsigned DimensionEx::getExpWidth() const { return __exp_width; }

unsigned DimensionEx::getExpHeight() const { return __exp_height; }

unsigned DimensionEx::getWidth() const { return __width; }

unsigned DimensionEx::getHeight() const { return __height; }

void InsufficientDimensionsEx::__print_args(std::ostream &os) const {
    os  << "minWidth: " << getExpWidth() << " minHeight: " << getExpHeight()
        << "\nwidth: " << getWidth() << " height: " << getHeight() << "\n";
}

InsufficientDimensionsEx::InsufficientDimensionsEx
        (unsigned minWidth, unsigned minHeight,unsigned width, unsigned height)
        : DimensionEx(minWidth, minHeight, width, height) { setName ("InsufficientDimensionsEx"); }

void OutOfBoundsEx::__print_args(std::ostream &os) const {
    os  << "minWidth: " << getExpWidth() << " minHeight: " << getExpHeight();
    os  << "\nwidth: " << getWidth() << " height: " << getHeight() << "\n";
}

OutOfBoundsEx::OutOfBoundsEx
        (unsigned maxWidth, unsigned maxHeight, unsigned width, unsigned height)
        : DimensionEx(maxWidth, maxHeight, width, height){ setName("OutOfBoundsEx"); }

void PositionEx::__print_args(std::ostream &os) const { os << "x: " << __x << " y: " << __y << "\n"; }

PositionEx::PositionEx(unsigned x, unsigned y) {
    __y = y;
    __x = x;
    setName("PositionEx");
}

PositionEmptyEx::PositionEmptyEx(unsigned x, unsigned y) : PositionEx(x, y) { setName ("PositionNonemptyEx"); }

void PosVectorEmptyEx::__print_args(std::ostream &os) const {}

PosVectorEmptyEx::PosVectorEmptyEx() : GamingException() { setName("PosVectorEmptyEx"); }

PositionNonemptyEx::PositionNonemptyEx(unsigned x, unsigned y) : PositionEx(x, y) { setName("PositionNonemptyEx"); }
