// FILE: stats.cxx
// Written by:
// Nate Sands (nsands@citymail.cuny.edu)
// (last modified 23:15 09122019)
//
// CSc212 DataStructures
// Assignment 1
// Fall 2019
// City College of New York
// Prof. Theresa Crupi
//
// CLASS IMPLEMENTED: statistician (see stats.h for documentation)

#include <cassert>
#include "stats.h"
#include <cmath>

namespace fa19_assgn1
{
  // CONSTRUCTOR
  statistician::statistician()
  {
    count = 0;
    total = 0;
  }

  // MODIFICATION MEMBER FUNCTIONS
  void statistician::next(double r)
  // updates: count, total, min, max, rec,
  // abs_min, abs_max
  {
    if (count == 0) {
      total = r;
      min = r;
      max = r;
      abs_min = std::abs(r);
      abs_max = std::abs(r);
    }
    else {
      assert(count > 0);
      total += r;
      if (r < min) min = r;
      if (r > max) max = r;
      if (std::abs(r) > abs_max) abs_max = std::abs(r);
      if (std::abs(r) < abs_min) abs_min = std::abs(r);
    }
    rec = r;
    count++;
  }

  void statistician::reset()
  {
    count = 0;
    total = 0;
  }
  // CONSTANT MEMBER FUNCTIONS
  double statistician::mean() const
  {
    assert(count > 0);
    return total / count;
  }
  double statistician::recent() const
  {
    assert(count > 0);
    return rec;
  }
  double statistician::minimum() const
  {
    assert(count > 0);
    return min;
  }
  double statistician::maximum() const
  {
    assert(count > 0);
    return max;
  }
  double statistician::abs_minimum() const
  {
    assert(count > 0);
    return abs_min;
  }
  double statistician::abs_maximum() const
  {
    assert(count > 0);
    return abs_max;
  }
  // FRIEND FUNCTIONS
  statistician operator +
    (const statistician& s1, const statistician& s2)
  {
    statistician s3;
    if (s1.count == 0 && s2.count == 0) return s3;
    else if (s1.count == 0) return s2;
    else if (s2.count == 0) return s1;
    else {
      s3.count = s1.count + s2.count;
      s3.total = s1.total + s2.total;
      if (s1.min <= s2.min) s3.min = s1.min;
      else s3.min = s2.min;
      s3.rec = s2.rec;
      if (s1.max >= s2.max) s3.max = s1.max;
      else s3.max = s2.max;
      if (s1.abs_min <= s2.abs_min) s3.abs_min = s1.abs_min;
      else s3.abs_min = s2.abs_min;
      if (s1.abs_max >= s2.abs_max) s3.abs_max = s1.abs_max;
      else s3.abs_max = s2.abs_max;
    }
    return s3;
  }
  statistician operator *
    (double scale, const statistician& s)
  {
    if (s.count == 0) return s;
    statistician scaled;
    scaled.count = s.count;
    scaled.total = scale * s.total;
    if (scale < 0) {
      scaled.min = scale * s.max;
      scaled.max = scale * s.min;
    }
    else {
      scaled.min = scale * s.min;
      scaled.max = scale * s.max;
    }
    scaled.rec = s.rec * scale;
    scaled.abs_min = std::abs(scale * s.abs_min);
    scaled.abs_max = std::abs(scale * s.abs_max);
    return scaled;
  }
  // NON-MEMBER functions for statistician class
  bool operator ==(const statistician& s1, const statistician& s2)
  {
    if (s1.length() == 0 && s2.length() == 0) return true;
    else if (s1.length() == s2.length() &&
             s1.sum() == s2.sum() &&
             s1.mean() == s2.mean() &&
             s1.maximum() == s2.maximum() &&
             s1.minimum() == s2.minimum() &&
             s1.abs_maximum() == s2.abs_maximum() &&
             s1.abs_minimum() == s2.abs_minimum()) return true;
    else return false;
  }
}
