#include "ZeroSolver.hpp"
#include "extendedAssert.hpp"


ResultType Bisection::solve (){

  ResultType res;
  double a=options.a;
  double b=options.b;

  unsigned it=0;

  double ya = m_f(a);
  double yb = m_f(b);
  double delta = b - a;
  SURE_ASSERT(ya * yb < 0, "Function must change sign at the two end values");
  double yc{ya};
  double c{a};
  while(std::abs(delta) > 2 * options.tol)
    {
      c = (a + b) / 2.;
      yc = m_f(c);
      if(yc * ya < 0.0)
        {
          yb = yc;
          b = c;
        }
      else
        {
          ya = yc;
          a = c;
        }
      delta = b - a;
      it++;
    }
    res.solution=(a + b) / 2.;
    res.iteration=it;

  return res;
}

ResultType QuasiNewton::solve(){

  ResultType res;
  double a=options.a;

  double       ya = m_f(a);
  double       resid = std::abs(ya);
  unsigned int iter{0u};
  double       check = options.tol * resid + options.tola;
  bool         goOn = resid > check;
  while(goOn && iter < options.max_iter)
    {
      ++iter;
      a += - ya/m_Df(a);
      ya = m_f(a);
      resid = std::abs(ya);
      goOn = resid > check;
    }

    res.solution=a;
    res.converged=iter<options.max_iter;
    res.iteration=iter;

    return res;

}

ResultType Secant::solve(){


  double a =options.a;
  double b=options.b;
  double tol=options.tol;
  double tola=options.tola;
  unsigned int maxIt=options.max_iter;

  ResultType res;

  double       ya = m_f(a);
  double       resid = std::abs(ya);
  double       c{a};
  unsigned int iter{0u};
  double       check = tol * resid + tola;
  bool         goOn = resid > check;
  while(goOn && iter < maxIt)
    {
      ++iter;
      double yb = m_f(b);
      c = a - ya * (b - a) / (yb - ya);
      double yc = m_f(c);
      resid = std::abs(yc);
      goOn = resid > check;
      ya = yc;
      a = c;
    }

    res.solution=c;
    res.converged=iter<maxIt;
    res.iteration=iter;

  return res;

}


