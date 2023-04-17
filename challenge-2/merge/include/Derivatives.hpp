/*
 * Code adapted from Derivatives.hpp in Examples/Derivatives
 */

#ifndef DERIVATIVES_HPP
#define DERIVATIVES_HPP

#include <functional>
#include <type_traits>

namespace apsc {

    namespace DifferenceType {
        struct BACKWARD;
        struct FORWARD {
            using otherType = BACKWARD;
        };
      struct BACKWARD {
          using otherType = FORWARD;
      };
      struct CENTERED {
          using otherType = CENTERED;
      };
    } /* namespace DifferenceType */

    /*!
     * Computes the Nth derivative of a function by finite difference.
     * 
     * \tparam N the order of the derivative
     * \tparam F the callable object of signature T (T const &)
     * \tparam T The argument and return type of the callable object
     * \tparam DT The type of differencing: either DifferenceType::FORWARD or
     * DifferenceType::BACKWARD or DifferenceType::CENTERED
     */
    template <unsigned N, typename F, typename T = double, typename DT = DifferenceType::FORWARD>
    class NthDerivative {
        public:
            using PreviousDerivative = NthDerivative<N - 1, F, T, typename DT::otherType>;
            NthDerivative(const F &f, T h): pDerivative{f, h}, h{h} {}
            T operator()(const T &x) const {
                if constexpr(std::is_same<DifferenceType::FORWARD, DT>::value)
                    return (pDerivative(x + h) - pDerivative(x)) / h;
                else if constexpr(std::is_same<DifferenceType::BACKWARD, DT>::value)
                    return (pDerivative(x) - pDerivative(x - h)) / h;
                else
                    return (pDerivative(x + h) - pDerivative(x - h)) / (2 * h);
            }
        private:
            PreviousDerivative pDerivative;
            const T h;
    };

    /*!
    * Specialization for the 1st derivative
    * @tparam F A callable object type
    * @tparam T The type of the varaible
    * @tparam DT The difference type
    */
    template <typename F, typename T, typename DT>
    class NthDerivative<1u, F, T, DT> {
        public:
            NthDerivative(const F &f, T h): f{f}, h{h} {}
            T operator()(const T &x) const {
                if constexpr(std::is_same_v<DifferenceType::FORWARD, DT>)
                    return (f(x + h) - f(x)) / h;
                else if constexpr(std::is_same_v<DifferenceType::BACKWARD, DT>)
                    return (f(x) - f(x - h)) / h;
                else
                    return (f(x + h) - f(x - h)) / (2. * h);
              }
        private:
            F const &f;
            T const h;
    };

    /*! 
    * For consistency only: 0th derivative
    */
    template <typename F, typename T, typename DT>
    class NthDerivative<0u, F, T, DT> {
        public:
        NthDerivative(const F &f, T h): f{f}, h{h} {}
        T operator()(const T &x) const { return f(x); }
        private:
            F const &f;
            T const h;
    };

    /*!
    * Utility to simplify the creation of a Nthderivative object
    *
    * @param f Callable function with the rigth signature
    * @param h Step for computing derivatives
    */
    template <unsigned N, typename F, typename T>
    auto  makeForwardDerivative(const F &f, const T &h) {
        return NthDerivative<N, F, T, DifferenceType::FORWARD>{f, h};
    }

    /*!
    * Utility to simplify the creation of a Nthderivative object.
    *
    * @param f Callable function with the rigth signature
    * @param h Step for computing derivatives
    */
    template <unsigned N, typename F, typename T>
    auto makeBackwardDerivative(const F &f, const T &h) {
        return NthDerivative<N, F, T, DifferenceType::BACKWARD>{f, h};
    }

    /*!
    * Utility to simplify the creation of a Nthderivative object
    *
    * @param f Callable function with the rigth signature
    * @param h Step for computing derivatives
    */
    template <unsigned N, typename F, typename T>
    auto makeCenteredDerivative(const F &f, const T &h) {
        return NthDerivative<N, F, T, DifferenceType::CENTERED>{f, h};
    }
} /* namespace apsc */

#endif /* Derivatives */
