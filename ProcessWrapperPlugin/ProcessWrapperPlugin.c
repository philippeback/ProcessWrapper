/* Automatically generated from Squeak on an Array(2 August 2007 6:27:43 pm) */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* Default EXPORT macro that does nothing (see comment in sq.h): */
#define EXPORT(returnType) returnType

/* Do not include the entire sq.h file but just those parts needed. */
/*  The virtual machine proxy definition */
#include "sqVirtualMachine.h"
/* Configuration options */
#include "sqConfig.h"
/* Platform specific definitions */
#include "sqPlatformSpecific.h"

#define true 1
#define false 0
#define null 0  /* using 'null' because nil is predefined in Think C */
#ifdef SQUEAK_BUILTIN_PLUGIN
#undef EXPORT
// was #undef EXPORT(returnType) but screws NorCroft cc
#define EXPORT(returnType) static returnType
#endif
#include "ProcessWrapperPlugin.h"

/* memory access macros */
/*
#define byteAt(i) (*((unsigned char *) (i)))
#define byteAtput(i, val) (*((unsigned char *) (i)) = val)
#define longAt(i) (*((int *) (i)))
#define longAtput(i, val) (*((int *) (i)) = val)
*/

/*** Constants ***/

/*** Function Prototypes ***/
#pragma export on
EXPORT(const char*) getModuleName(void);
#pragma export off
static int halt(void);
static int msg(char *s);
#pragma export on
EXPORT(int) primitiveCloseStderr(void);
EXPORT(int) primitiveCloseStdin(void);
EXPORT(int) primitiveCloseStdout(void);
EXPORT(int) primitiveExitCode(void);
EXPORT(int) primitiveIsRunning(void);
EXPORT(int) primitiveLogLevelDebug(void);
EXPORT(int) primitiveLogLevelError(void);
EXPORT(int) primitiveLogLevelInfo(void);
EXPORT(int) primitiveLogLevelNone(void);
EXPORT(int) primitiveLogTest(void);
EXPORT(int) primitiveNewProcess(void);
EXPORT(int) primitivePluginVersion(void);
EXPORT(int) primitiveReadFromStderrIntoSize(void);
EXPORT(int) primitiveReadFromStdoutIntoSize(void);
EXPORT(int) primitiveRemoveProcess(void);
EXPORT(int) primitiveSetStderrSemaphoreFor(void);
EXPORT(int) primitiveSetStdoutSemaphoreFor(void);
EXPORT(int) primitiveSetWaiterSemaphoreFor(void);
EXPORT(int) primitiveShowWindowAtStartup(void);
EXPORT(int) primitiveStartProcessWithCommandLine(void);
EXPORT(int) primitiveTerminate(void);
EXPORT(int) primitiveWriteToStdinMessageLength(void);
EXPORT(int) setInterpreter(struct VirtualMachine* anInterpreter);
EXPORT(int) signalSemaphore(int aSemaphoreIndex);
#pragma export off
static int sqAssert(int aBool);
/*** Variables ***/

#ifdef SQUEAK_BUILTIN_PLUGIN
extern
#endif
struct VirtualMachine* interpreterProxy;
static const char *moduleName =
#ifdef SQUEAK_BUILTIN_PLUGIN
	"ProcessWrapperPlugin 2 August 2007 (i)"
#else
	"ProcessWrapperPlugin 2 August 2007 (e)"
#endif
;



/*	Note: This is hardcoded so it can be run from Squeak.
	The module name is used for validating a module *after*
	it is loaded to check if it does really contain the module
	we're thinking it contains. This is important! */

EXPORT(const char*) getModuleName(void) {
	return moduleName;
}

static int halt(void) {
	;
}

static int msg(char *s) {
	fprintf(stderr, "\n%s: %s", moduleName, s);
}

EXPORT(int) primitiveCloseStderr(void) {
	BOOL result;
	unsigned anExternalProcessPointer;
	int _return_value;

	anExternalProcessPointer = interpreterProxy->positive32BitValueOf(interpreterProxy->stackValue(0));
	if (interpreterProxy->failed()) {
		return null;
	}
	result = close_stderr(anExternalProcessPointer);
	_return_value = (result? interpreterProxy->trueObject(): interpreterProxy->falseObject());
	if (interpreterProxy->failed()) {
		return null;
	}
	interpreterProxy->popthenPush(2, _return_value);
	return null;
}

EXPORT(int) primitiveCloseStdin(void) {
	BOOL result;
	unsigned anExternalProcessPointer;
	int _return_value;

	anExternalProcessPointer = interpreterProxy->positive32BitValueOf(interpreterProxy->stackValue(0));
	if (interpreterProxy->failed()) {
		return null;
	}
	result = close_stdin(anExternalProcessPointer);
	_return_value = (result? interpreterProxy->trueObject(): interpreterProxy->falseObject());
	if (interpreterProxy->failed()) {
		return null;
	}
	interpreterProxy->popthenPush(2, _return_value);
	return null;
}

EXPORT(int) primitiveCloseStdout(void) {
	BOOL result;
	unsigned anExternalProcessPointer;
	int _return_value;

	anExternalProcessPointer = interpreterProxy->positive32BitValueOf(interpreterProxy->stackValue(0));
	if (interpreterProxy->failed()) {
		return null;
	}
	result = close_stdout(anExternalProcessPointer);
	_return_value = (result? interpreterProxy->trueObject(): interpreterProxy->falseObject());
	if (interpreterProxy->failed()) {
		return null;
	}
	interpreterProxy->popthenPush(2, _return_value);
	return null;
}

EXPORT(int) primitiveExitCode(void) {
	DWORD result;
	unsigned anExternalProcessPointer;
	int _return_value;

	anExternalProcessPointer = interpreterProxy->positive32BitValueOf(interpreterProxy->stackValue(0));
	if (interpreterProxy->failed()) {
		return null;
	}
	result = terminate(anExternalProcessPointer);
	_return_value = interpreterProxy->positive32BitIntegerFor(result);
	if (interpreterProxy->failed()) {
		return null;
	}
	interpreterProxy->popthenPush(2, _return_value);
	return null;
}

EXPORT(int) primitiveIsRunning(void) {
	BOOL result;
	unsigned anExternalProcessPointer;
	int _return_value;

	anExternalProcessPointer = interpreterProxy->positive32BitValueOf(interpreterProxy->stackValue(0));
	if (interpreterProxy->failed()) {
		return null;
	}
	result = is_running(anExternalProcessPointer);
	_return_value = (result? interpreterProxy->trueObject(): interpreterProxy->falseObject());
	if (interpreterProxy->failed()) {
		return null;
	}
	interpreterProxy->popthenPush(2, _return_value);
	return null;
}

EXPORT(int) primitiveLogLevelDebug(void) {
	log_level_debug();
	if (interpreterProxy->failed()) {
		return null;
	}
	return null;
}

EXPORT(int) primitiveLogLevelError(void) {
	log_level_error();
	if (interpreterProxy->failed()) {
		return null;
	}
	return null;
}

EXPORT(int) primitiveLogLevelInfo(void) {
	log_level_info();
	if (interpreterProxy->failed()) {
		return null;
	}
	return null;
}

EXPORT(int) primitiveLogLevelNone(void) {
	log_level_none();
	if (interpreterProxy->failed()) {
		return null;
	}
	return null;
}

EXPORT(int) primitiveLogTest(void) {
	log_test();
	if (interpreterProxy->failed()) {
		return null;
	}
	return null;
}

EXPORT(int) primitiveNewProcess(void) {
	DWORD result;
	int _return_value;

	result = new_process();
	_return_value = interpreterProxy->positive32BitIntegerFor(result);
	if (interpreterProxy->failed()) {
		return null;
	}
	interpreterProxy->popthenPush(1, _return_value);
	return null;
}


/*	This method is generated! */

EXPORT(int) primitivePluginVersion(void) {
	int _return_value;

	_return_value = interpreterProxy->integerObjectOf(2);
	if (interpreterProxy->failed()) {
		return null;
	}
	interpreterProxy->popthenPush(1, _return_value);
	return null;
}

EXPORT(int) primitiveReadFromStderrIntoSize(void) {
	DWORD result;
	unsigned anExternalProcessPointer;
	char* aByteArray;
	unsigned anInteger;
	int _return_value;

	anExternalProcessPointer = interpreterProxy->positive32BitValueOf(interpreterProxy->stackValue(2));
	aByteArray = ((char *) (interpreterProxy->arrayValueOf(interpreterProxy->stackValue(1))));
	anInteger = interpreterProxy->positive32BitValueOf(interpreterProxy->stackValue(0));
	if (interpreterProxy->failed()) {
		return null;
	}
	result = read_from_stderr(anExternalProcessPointer, aByteArray, anInteger);
	_return_value = interpreterProxy->positive32BitIntegerFor(result);
	if (interpreterProxy->failed()) {
		return null;
	}
	interpreterProxy->popthenPush(4, _return_value);
	return null;
}

EXPORT(int) primitiveReadFromStdoutIntoSize(void) {
	DWORD result;
	unsigned anExternalProcessPointer;
	char* aByteArray;
	unsigned anInteger;
	int _return_value;

	anExternalProcessPointer = interpreterProxy->positive32BitValueOf(interpreterProxy->stackValue(2));
	aByteArray = ((char *) (interpreterProxy->arrayValueOf(interpreterProxy->stackValue(1))));
	anInteger = interpreterProxy->positive32BitValueOf(interpreterProxy->stackValue(0));
	if (interpreterProxy->failed()) {
		return null;
	}
	result = read_from_stdout(anExternalProcessPointer, aByteArray, anInteger);
	_return_value = interpreterProxy->positive32BitIntegerFor(result);
	if (interpreterProxy->failed()) {
		return null;
	}
	interpreterProxy->popthenPush(4, _return_value);
	return null;
}

EXPORT(int) primitiveRemoveProcess(void) {
	BOOL result;
	unsigned anExternalProcessPointer;
	int _return_value;

	anExternalProcessPointer = interpreterProxy->positive32BitValueOf(interpreterProxy->stackValue(0));
	if (interpreterProxy->failed()) {
		return null;
	}
	result = remove_process(anExternalProcessPointer);
	_return_value = (result? interpreterProxy->trueObject(): interpreterProxy->falseObject());
	if (interpreterProxy->failed()) {
		return null;
	}
	interpreterProxy->popthenPush(2, _return_value);
	return null;
}

EXPORT(int) primitiveSetStderrSemaphoreFor(void) {
	unsigned aSemaphoreIndex;
	unsigned anExternalProcessPointer;

	aSemaphoreIndex = interpreterProxy->positive32BitValueOf(interpreterProxy->stackValue(1));
	anExternalProcessPointer = interpreterProxy->positive32BitValueOf(interpreterProxy->stackValue(0));
	if (interpreterProxy->failed()) {
		return null;
	}
	set_stderr_semaphore(anExternalProcessPointer, aSemaphoreIndex);
	if (interpreterProxy->failed()) {
		return null;
	}
	interpreterProxy->pop(2);
	return null;
}

EXPORT(int) primitiveSetStdoutSemaphoreFor(void) {
	unsigned aSemaphoreIndex;
	unsigned anExternalProcessPointer;

	aSemaphoreIndex = interpreterProxy->positive32BitValueOf(interpreterProxy->stackValue(1));
	anExternalProcessPointer = interpreterProxy->positive32BitValueOf(interpreterProxy->stackValue(0));
	if (interpreterProxy->failed()) {
		return null;
	}
	set_stdout_semaphore(anExternalProcessPointer, aSemaphoreIndex);
	if (interpreterProxy->failed()) {
		return null;
	}
	interpreterProxy->pop(2);
	return null;
}

EXPORT(int) primitiveSetWaiterSemaphoreFor(void) {
	unsigned aSemaphoreIndex;
	unsigned anExternalProcessPointer;

	aSemaphoreIndex = interpreterProxy->positive32BitValueOf(interpreterProxy->stackValue(1));
	anExternalProcessPointer = interpreterProxy->positive32BitValueOf(interpreterProxy->stackValue(0));
	if (interpreterProxy->failed()) {
		return null;
	}
	set_waiter_semaphore(anExternalProcessPointer, aSemaphoreIndex);
	if (interpreterProxy->failed()) {
		return null;
	}
	interpreterProxy->pop(2);
	return null;
}

EXPORT(int) primitiveShowWindowAtStartup(void) {
	BOOL result;
	unsigned anExternalProcessPointer;
	int _return_value;

	anExternalProcessPointer = interpreterProxy->positive32BitValueOf(interpreterProxy->stackValue(0));
	if (interpreterProxy->failed()) {
		return null;
	}
	result = show_window_at_startup(anExternalProcessPointer);
	_return_value = (result? interpreterProxy->trueObject(): interpreterProxy->falseObject());
	if (interpreterProxy->failed()) {
		return null;
	}
	interpreterProxy->popthenPush(2, _return_value);
	return null;
}

EXPORT(int) primitiveStartProcessWithCommandLine(void) {
	BOOL result;
	unsigned anExternalProcessPointer;
	char* aString;
	int _return_value;

	anExternalProcessPointer = interpreterProxy->positive32BitValueOf(interpreterProxy->stackValue(1));
	aString = ((char *) (interpreterProxy->arrayValueOf(interpreterProxy->stackValue(0))));
	if (interpreterProxy->failed()) {
		return null;
	}
	result = start_process(anExternalProcessPointer, aString);
	_return_value = (result? interpreterProxy->trueObject(): interpreterProxy->falseObject());
	if (interpreterProxy->failed()) {
		return null;
	}
	interpreterProxy->popthenPush(3, _return_value);
	return null;
}

EXPORT(int) primitiveTerminate(void) {
	BOOL result;
	unsigned anExternalProcessPointer;
	int _return_value;

	anExternalProcessPointer = interpreterProxy->positive32BitValueOf(interpreterProxy->stackValue(0));
	if (interpreterProxy->failed()) {
		return null;
	}
	result = terminate(anExternalProcessPointer);
	_return_value = (result? interpreterProxy->trueObject(): interpreterProxy->falseObject());
	if (interpreterProxy->failed()) {
		return null;
	}
	interpreterProxy->popthenPush(2, _return_value);
	return null;
}

EXPORT(int) primitiveWriteToStdinMessageLength(void) {
	BOOL result;
	unsigned anExternalProcessPointer;
	char* aByteArray;
	unsigned anInteger;
	int _return_value;

	anExternalProcessPointer = interpreterProxy->positive32BitValueOf(interpreterProxy->stackValue(2));
	aByteArray = ((char *) (interpreterProxy->arrayValueOf(interpreterProxy->stackValue(1))));
	anInteger = interpreterProxy->positive32BitValueOf(interpreterProxy->stackValue(0));
	if (interpreterProxy->failed()) {
		return null;
	}
	result = write_to_stdin(anExternalProcessPointer, aByteArray, anInteger);
	_return_value = (result? interpreterProxy->trueObject(): interpreterProxy->falseObject());
	if (interpreterProxy->failed()) {
		return null;
	}
	interpreterProxy->popthenPush(4, _return_value);
	return null;
}


/*	Note: This is coded so that is can be run from Squeak. */

EXPORT(int) setInterpreter(struct VirtualMachine* anInterpreter) {
	int ok;

	interpreterProxy = anInterpreter;
	ok = interpreterProxy->majorVersion() == VM_PROXY_MAJOR;
	if (ok == 0) {
		return 0;
	}
	ok = interpreterProxy->minorVersion() >= VM_PROXY_MINOR;
	return ok;
}

EXPORT(int) signalSemaphore(int aSemaphoreIndex) {
	interpreterProxy->signalSemaphoreWithIndex(aSemaphoreIndex);
}

static int sqAssert(int aBool) {
	/* missing DebugCode */;
}


#ifdef SQUEAK_BUILTIN_PLUGIN


void* ProcessWrapperPlugin_exports[][3] = {
	{"ProcessWrapperPlugin", "primitiveLogLevelError", (void*)primitiveLogLevelError},
	{"ProcessWrapperPlugin", "primitiveRemoveProcess", (void*)primitiveRemoveProcess},
	{"ProcessWrapperPlugin", "primitiveTerminate", (void*)primitiveTerminate},
	{"ProcessWrapperPlugin", "primitiveLogLevelInfo", (void*)primitiveLogLevelInfo},
	{"ProcessWrapperPlugin", "primitiveCloseStdin", (void*)primitiveCloseStdin},
	{"ProcessWrapperPlugin", "primitivePluginVersion", (void*)primitivePluginVersion},
	{"ProcessWrapperPlugin", "setInterpreter", (void*)setInterpreter},
	{"ProcessWrapperPlugin", "primitiveWriteToStdinMessageLength", (void*)primitiveWriteToStdinMessageLength},
	{"ProcessWrapperPlugin", "signalSemaphore", (void*)signalSemaphore},
	{"ProcessWrapperPlugin", "primitiveExitCode", (void*)primitiveExitCode},
	{"ProcessWrapperPlugin", "getModuleName", (void*)getModuleName},
	{"ProcessWrapperPlugin", "primitiveReadFromStdoutIntoSize", (void*)primitiveReadFromStdoutIntoSize},
	{"ProcessWrapperPlugin", "primitiveIsRunning", (void*)primitiveIsRunning},
	{"ProcessWrapperPlugin", "primitiveLogTest", (void*)primitiveLogTest},
	{"ProcessWrapperPlugin", "primitiveCloseStdout", (void*)primitiveCloseStdout},
	{"ProcessWrapperPlugin", "primitiveStartProcessWithCommandLine", (void*)primitiveStartProcessWithCommandLine},
	{"ProcessWrapperPlugin", "primitiveCloseStderr", (void*)primitiveCloseStderr},
	{"ProcessWrapperPlugin", "primitiveSetWaiterSemaphoreFor", (void*)primitiveSetWaiterSemaphoreFor},
	{"ProcessWrapperPlugin", "primitiveSetStderrSemaphoreFor", (void*)primitiveSetStderrSemaphoreFor},
	{"ProcessWrapperPlugin", "primitiveShowWindowAtStartup", (void*)primitiveShowWindowAtStartup},
	{"ProcessWrapperPlugin", "primitiveReadFromStderrIntoSize", (void*)primitiveReadFromStderrIntoSize},
	{"ProcessWrapperPlugin", "primitiveSetStdoutSemaphoreFor", (void*)primitiveSetStdoutSemaphoreFor},
	{"ProcessWrapperPlugin", "primitiveLogLevelDebug", (void*)primitiveLogLevelDebug},
	{"ProcessWrapperPlugin", "primitiveLogLevelNone", (void*)primitiveLogLevelNone},
	{"ProcessWrapperPlugin", "primitiveNewProcess", (void*)primitiveNewProcess},
	{NULL, NULL, NULL}
};


#endif /* ifdef SQ_BUILTIN_PLUGIN */

