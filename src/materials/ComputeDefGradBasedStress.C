//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "ComputeDefGradBasedStress.h"

registerMooseObject("testApp", ComputeDefGradBasedStress);

template <>
InputParameters
validParams<ComputeDefGradBasedStress>()
{
  InputParameters params = validParams<ComputeStressBase>();
  params.addClassDescription("Computes stress based on lagrangian strain");
  return params;
}

ComputeDefGradBasedStress::ComputeDefGradBasedStress(const InputParameters & parameters)
  : ComputeStressBase(parameters),
    GuaranteeConsumer(this),
    _deformation_gradient(getMaterialProperty<RankTwoTensor>(_base_name + "deformation_gradient"))
{
}

void
ComputeDefGradBasedStress::initialSetup()
{
  if (!hasGuaranteedMaterialProperty(_elasticity_tensor_name, Guarantee::ISOTROPIC))
    mooseError("ComputeFiniteStrainElasticStress can only be used with elasticity tensor materials "
               "that guarantee isotropic tensors.");
}
void
ComputeDefGradBasedStress::initQpStatefulProperties()
{
  ComputeStressBase::initQpStatefulProperties();
}


void
ComputeDefGradBasedStress::computeQpStress()
{
  const RankTwoTensor iden(RankTwoTensor::initIdentity);
  RankTwoTensor ee =
      0.5 * (_deformation_gradient[_qp].transpose() * _deformation_gradient[_qp] - iden);
  RankTwoTensor pk2 = _elasticity_tensor[_qp] * ee;

  _stress[_qp] = _deformation_gradient[_qp] * pk2 * _deformation_gradient[_qp].transpose() /
                 _deformation_gradient[_qp].det();
  _Jacobian_mult[_qp] = _elasticity_tensor[_qp];
}
