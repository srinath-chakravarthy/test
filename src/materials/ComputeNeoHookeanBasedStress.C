/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ComputeNeoHokkeanBasedStress.C
 * Author: srinath
 * 
 * Created on July 5, 2018, 3:09 PM
 */

#include "ComputeNeoHookeanBasedStress.h"
#include "ElasticityTensorTools.h"
#include "libmesh/utility.h"


ComputeNeoHookeanBasedStress::ComputeNeoHookeanBasedStress(const InputParameters & parameters)
  :ComputeDefGradBasedStress(parameters)
{  
}

void
ComputeNeoHookeanBasedStress::computeQpStress()
{
        
    RankTwoTensor II(RankTwoTensor::initIdentity);
    RankTwoTensor B = _deformation_gradient[_qp] * _deformation_gradient[_qp].transpose();
    Real shear_modulus = ElasticityTensorTools::getIsotropicShearModulus(_elasticity_tensor[_qp]);
    Real bulk_modulus = ElasticityTensorTools::getIsotropicBulkModulus(_elasticity_tensor[_qp]);
    Real J = _deformation_gradient[_qp].det();
    Real pow = 5.0/3.0;
    Real pow2 = 2.0/3.0;
    Real onethird = 1.0/3.0;
    Real pref1 = shear_modulus/std::pow(J, pow);
    Real pref2 = shear_moulus/std::pow(J,pow2);
    _stress[_qp] = pref1*(B - onethird*B.trace()*II);
    _stress[_qp] += bulk_modulus*(J-1.0)*II;
    RankFourTensor term1 = II.mixedProductIkJl(B) + II.mixedProductIlJk(B);
    RankFourTensor term2 = B.outerProduct(II) + II.outerProduct(B);
    RankFourTensor term3 = B.trace()*(II.outerProduct(II));
    _Jacobian_mult = pref2*(term1 - 2.0*onethird*term2 + 2.0*onethird*onethird*term3);
    _Jacobian_mult = bulk_modulus*(2.0*J -1)*(II.outerProduct(II));
}