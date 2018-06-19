//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html
#include "testTestApp.h"
#include "testApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "MooseSyntax.h"
#include "ModulesApp.h"

template <>
InputParameters
validParams<testTestApp>()
{
  InputParameters params = validParams<testApp>();
  return params;
}

testTestApp::testTestApp(InputParameters parameters) : MooseApp(parameters)
{
  Moose::registerObjects(_factory);
  ModulesApp::registerObjects(_factory);
  testApp::registerObjectDepends(_factory);
  testApp::registerObjects(_factory);

  Moose::associateSyntax(_syntax, _action_factory);
  ModulesApp::associateSyntax(_syntax, _action_factory);
  testApp::associateSyntaxDepends(_syntax, _action_factory);
  testApp::associateSyntax(_syntax, _action_factory);

  Moose::registerExecFlags(_factory);
  ModulesApp::registerExecFlags(_factory);
  testApp::registerExecFlags(_factory);

  bool use_test_objs = getParam<bool>("allow_test_objects");
  if (use_test_objs)
  {
    testTestApp::registerObjects(_factory);
    testTestApp::associateSyntax(_syntax, _action_factory);
    testTestApp::registerExecFlags(_factory);
  }
}

testTestApp::~testTestApp() {}

void
testTestApp::registerApps()
{
  registerApp(testApp);
  registerApp(testTestApp);
}

void
testTestApp::registerObjects(Factory & /*factory*/)
{
  /* Uncomment Factory parameter and register your new test objects here! */
}

void
testTestApp::associateSyntax(Syntax & /*syntax*/, ActionFactory & /*action_factory*/)
{
  /* Uncomment Syntax and ActionFactory parameters and register your new test objects here! */
}

void
testTestApp::registerExecFlags(Factory & /*factory*/)
{
  /* Uncomment Factory parameter and register your new execute flags here! */
}

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
// External entry point for dynamic application loading
extern "C" void
testTestApp__registerApps()
{
  testTestApp::registerApps();
}

// External entry point for dynamic object registration
extern "C" void
testTestApp__registerObjects(Factory & factory)
{
  testTestApp::registerObjects(factory);
}

// External entry point for dynamic syntax association
extern "C" void
testTestApp__associateSyntax(Syntax & syntax, ActionFactory & action_factory)
{
  testTestApp::associateSyntax(syntax, action_factory);
}

// External entry point for dynamic execute flag loading
extern "C" void
testTestApp__registerExecFlags(Factory & factory)
{
  testTestApp::registerExecFlags(factory);
}
