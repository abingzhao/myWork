/*******************************************************************************
    File        : sList.h
    Description : Application of single List: Polynomial Operatorations;
                  Implement Some Basic Operations on Polynomial.
                  Include :
                    --Add 
                    --Subtract 
                    --Multiply 
                    --Divide
    Author      : abing0513

    Revision History
    ----------    ---------    --------------------------------------------
    2014-08-09    abing0513    Add Header file. Add Declare of The class;
                               Add The Boost::shared_ptr part.
                               Implement the Construtor and UpdateCoef();   
    2014-08-10    abing0513    Implement The PolyAdd and PolyMultiply
                                PolySubtract
*******************************************************************************/


#ifndef INCLUDE_POLYNOMIAL_HPP
#define INCLUDE_POLYNOMIAL_HPP

/*******************************************************************************
    INLCUDES
*******************************************************************************/
#include "sList.hpp"
#include <vector>
#include <list>
#include <deque>
#include <sstream>
#include <boost/format.hpp>
#include <boost/noncopyable.hpp>
/*******************************************************************************
    DEFINES
*******************************************************************************/

/*******************************************************************************
    CLASS DECLARE
*******************************************************************************/
/**
 * @tparam T  Sequential container :Vector/List/Deque
 */
template <typename T>
class polynomial:public boost::noncopyable 
{
private:
    sList<int>  coefficiet;
    int  maxOrder;
    /**
     * @param _coef Sequential container that stored The Polynomial Coefficient
     *              lowOrder->hignOrder
     */
    polynomial(const T& _coef, const int _maxOrder)
     : maxOrder(_maxOrder)
    {
        UpdateCoef(_coef,maxOrder);
    }
public:
    typedef boost::shared_ptr<polynomial<T> > sptr;
    static sptr make(  const T& _coef = static_cast<T>(0)
                     , const int _maxOrder = 0 )
    {
        return polynomial<T>::sptr(new polynomial(_coef,_maxOrder));
    } 
    //--------------------------------------------------------------------------

    ~polynomial()
    {
        if(!coefficiet.ListEmpty())
            coefficiet.ListClear();
    }
    sList<int> & GetCoef()
    {
        return coefficiet;
    }
    int MaxOrder() const
    {
        return maxOrder;
    }
    void UpdateCoef(const T& _coef, const int _maxOrder = 0)
    {
        maxOrder = _maxOrder;
        if(_coef.empty() || maxOrder == 0)
        {
            std::stringstream ss;
            ss  << "Cannot Construct the Polynomial With NO coefficient\n"
                << "and zero maxOrder!\n";
            throw std::runtime_error(ss.str());
        }
        int _coefLen = static_cast<int>(_coef.size());

        // std::cout<<"In func: "<<__func__<< " Line :"<<__LINE__
        //          <<"\n\t _coefLen = "<<_coefLen
        //          <<"\n\t maxOrder = "<<maxOrder<<std::endl;
        maxOrder = std::max(_coefLen - 1,maxOrder);
        if(!coefficiet.ListEmpty())
            coefficiet.ListClear();
        for (int i = 0; i <= maxOrder; ++i)
        {
            // IN coef:lowOrder -> highOrder
            coefficiet.PushBack(_coef[i]);
        }
    }
    void PrintPolynomial()
    {
        if(maxOrder != coefficiet.ListLength() - 1)
        {
            std::stringstream ss;
            ss<<"Error: The maxOrder does not Match The Coefficient length\n";
            throw std::runtime_error(ss.str());
        }
        int _maxOrder = static_cast<int>(maxOrder);
        for (int i = _maxOrder; i >= 0; --i)
        {
            if(0 != i)
                std::cout<<coefficiet[i]<<"x^"<<i<<" + ";
            else
                std::cout<<coefficiet[i];
        }
        std::cout<<std::endl;
    }

};
//------------------------------------------------------------------------------
template<typename T>
typename polynomial<T>::sptr  
PolyAdd(const typename polynomial<T>::sptr polyLhs, 
        const typename polynomial<T>::sptr polyRhs)
{
    int _maxOrderLhs = polyLhs->MaxOrder();
    int _maxOrderRhs = polyRhs->MaxOrder();
    int _minOrder = std::min(_maxOrderLhs, _maxOrderRhs);
    int _maxOrder    = std::max(_maxOrderLhs, _maxOrderRhs);
    // std::cout << "\n\t _maxOrderLhs = " << _maxOrderLhs
    //           << "\n\t _maxOrderRhs = " << _maxOrderRhs
    //           << "\n\t _maxOrder    = " << _maxOrder
    //           << "\n\t _minOrder    = " << _minOrder<<std::endl; 
    if(0 == _maxOrder)
    {
        std::stringstream ss;
        ss  <<"In "<<__func__<<" Line: "<<__LINE__
            <<"\n\tError: The Input Polynomial Is Invalid! Cannot Add\n";
        throw std::runtime_error(ss.str());
    }
    T _coef;
    // std::cout << "\n\t Coef Size = " << _coef.size() << std::endl;
    for (int i = 0; i <= _minOrder; ++i)
    {
        int tmpCoef = polyLhs->GetCoef().GetEleAt(i) + polyRhs->GetCoef().GetEleAt(i);
        _coef.push_back(tmpCoef);
    }

    typename polynomial<T>::sptr polyTmp;
    polyTmp = _maxOrderLhs > _maxOrderRhs ? polyLhs:polyRhs;
    for (int i = _minOrder + 1; i <= _maxOrder; ++i)
    {
        int tmpCoef = polyTmp->GetCoef().GetEleAt(i); 
        _coef.push_back(tmpCoef);
    }
    typename polynomial<T>::sptr polyRes;
    polyRes = polynomial<T>::make(_coef, _maxOrder);
    return polyRes;
}
template<typename T>
typename polynomial<T>::sptr  
PolyMultiply(const typename polynomial<T>::sptr polyLhs, 
             const typename polynomial<T>::sptr polyRhs)
{
    int _maxOrderLhs = polyLhs->MaxOrder(); 
    int _maxOrderRhs = polyRhs->MaxOrder();
    int _maxOrder    = _maxOrderLhs + _maxOrderRhs;
    if(0 == _maxOrder)
    {
        std::stringstream ss;
        ss  <<"In "<<__func__<<" Line: "<<__LINE__
            <<"\n\tError: The Input Polynomial Is Invalid! Cannot Add\n";
        throw std::runtime_error(ss.str());
    }
    T _coef(_maxOrder+1,0);

    for (int i = 0; i <= _maxOrderLhs; ++i)
    {
        int tmpCoefLhs = polyLhs->GetCoef().GetEleAt(i);
        for (int j = 0; j <= _maxOrderRhs; ++j)
        {
            int tmpCoefRes = _coef[i + j];
            int tmpCoefRhs = polyRhs->GetCoef().GetEleAt(j);
            tmpCoefRes += tmpCoefLhs * tmpCoefRhs;
            _coef[i+j] = tmpCoefRes;
        }
    }
    typename polynomial<T>::sptr polyRes;
    polyRes = polynomial<T>::make(_coef, _maxOrder);
    return polyRes;
}
template<typename T>
typename polynomial<T>::sptr  
PolySubtract(const typename polynomial<T>::sptr polyLhs, 
              const typename polynomial<T>::sptr polyRhs)
{
    // typename polynomial<T>::sptr polyTmp = polyRhs;
    int _maxOrderRhs = polyRhs->MaxOrder();
    for (int i = 0; i <= _maxOrderRhs; ++i)
    {
        int _coefTmp = polyRhs->GetCoef().GetEleAt(i);
        polyRhs->GetCoef().SetEleAt(i,-1*_coefTmp);
    }
    typename polynomial<T>::sptr polyRes = 
            PolyAdd<std::vector<int> >(polyLhs,polyRhs); 
    for (int i = 0; i <= _maxOrderRhs; ++i)
    {
        int _coefTmp = polyRhs->GetCoef().GetEleAt(i);
        polyRhs->GetCoef().SetEleAt(i,-_coefTmp);
    }
    return polyRes;
}
#endif/*INCLUDE_POLYNOMIAL_HPP*/