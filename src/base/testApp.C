#include "testApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"
#include "MooseSyntax.h"

template <>
InputParameters
validParams<testApp>()
{
  InputParameters params = validParams<MooseApp>();
  return params;
}

testApp::testApp(InputParameters parameters) : MooseApp(parameters)
{
  Moose::registerObjects(_factory);
  ModulesApp::registerObjects(_factory);
  testApp::registerObjects(_factory);

  Moose::associateSyntax(_syntax, _action_factory);
  ModulesApp::associateSyntax(_syntax, _action_factory);
  testApp::associateSyntax(_syntax, _action_factory);

  Moose::registerExecFlags(_factory);
  ModulesApp::registerExecFlags(_factory);
  testApp::registerExecFlags(_factory);
}

testApp::~testApp() {}

void
testApp::registerApps()
{
  registerApp(testApp);
}

void
testApp::registerObjects(Factory & factory)
{
    Registry::registerObjectsTo(factory, {"testApp"});
}

void
testApp::associateSyntax(Syntax & /*syntax*/, ActionFactory & action_factory)
{
  Registry::registerActionsTo(action_factory, {"testApp"});

  /* Uncomment Syntax parameter and register your new production objects here! */
}

void
testApp::registerObjectDepends(Factory & /*factory*/)
{
}

void
testApp::associateSyntaxDepends(Syntax & /*syntax*/, ActionFactory & /*action_factory*/)
{
}

void
testApp::registerExecFlags(Factory & /*factory*/)
{
  /* Uncomment Factory parameter and register your new execution flags here! */
}

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
extern "C" void
testApp__registerApps()
{
  testApp::registerApps();
}

extern "C" void
testApp__registerObjects(Factory & factory)
{
  testApp::registerObjects(factory);
}

extern "C" void
testApp__associateSyntax(Syntax & syntax, ActionFactory & action_factory)
{
  testApp::associateSyntax(syntax, action_factory);
}

extern "C" void
testApp__registerExecFlags(Factory & factory)
{
  testApp::registerExecFlags(factory);
}
