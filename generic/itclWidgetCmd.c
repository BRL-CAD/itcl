/*
 * ------------------------------------------------------------------------
 *      PACKAGE:  [incr Tcl]
 *  DESCRIPTION:  Object-Oriented Extensions to Tcl
 *
 * Implementation of commands for package ItclWidget
 *
 * This implementation is based mostly on the ideas of snit
 * whose author is William Duquette.
 *
 * ========================================================================
 *  Author: Arnulf Wiedemann
 *
 *     RCS:  $Id: itclWidgetCmd.c,v 1.1.2.6 2007/10/07 12:32:37 wiede Exp $
 * ========================================================================
 *           Copyright (c) 2007 Arnulf Wiedemann
 * ------------------------------------------------------------------------
 * See the file "license.terms" for information on usage and redistribution
 * of this file, and for a DISCLAIMER OF ALL WARRANTIES.
 */
#include "itclInt.h"


/*
 * ------------------------------------------------------------------------
 *  Itcl_TypeCmd()
 *
 *  Used to an [incr Tcl] type
 *
 *  Returns TCL_OK/TCL_ERROR to indicate success/failure.
 * ------------------------------------------------------------------------
 */
/* ARGSUSED */
int
Itcl_TypeCmd(
    ClientData clientData,   /* infoPtr */
    Tcl_Interp *interp,      /* current interpreter */
    int objc,                /* number of arguments */
    Tcl_Obj *CONST objv[])   /* argument objects */
{
    ItclClass *iclsPtr;
    ItclObjectInfo *infoPtr;
    int result;

    infoPtr = (ItclObjectInfo *)clientData;
    ItclShowArgs(1, "Itcl_TypeCmd", objc-1, objv);
    result = ItclClassBaseCmd(clientData, interp, ITCL_TYPE, objc, objv,
            &iclsPtr);
    return result;
}

/*
 * ------------------------------------------------------------------------
 *  Itcl_WidgetCmd()
 *
 *  Used to build an [incr Tcl] widget
 *
 *  Returns TCL_OK/TCL_ERROR to indicate success/failure.
 * ------------------------------------------------------------------------
 */
/* ARGSUSED */
int
Itcl_WidgetCmd(
    ClientData clientData,   /* infoPtr */
    Tcl_Interp *interp,      /* current interpreter */
    int objc,                /* number of arguments */
    Tcl_Obj *CONST objv[])   /* argument objects */
{
    Tcl_Obj *namePtr;
    ItclClass *iclsPtr;
    ItclObjectInfo *infoPtr;
    ItclVariable *ivPtr;
    int result;

    infoPtr = (ItclObjectInfo *)clientData;
    ItclShowArgs(1, "Itcl_WidgetCmd", objc-1, objv);
    result = ItclClassBaseCmd(clientData, interp, ITCL_WIDGET, objc, objv,
            &iclsPtr);
    if (result != TCL_OK) {
        return result;
    }
    if (!(iclsPtr->flags &(ITCL_WIDGET_FRAME|ITCL_WIDGET_TOPLEVEL))) {
        iclsPtr->flags |= ITCL_WIDGET_FRAME;
    }
    /* create the hull component */
    ItclComponent *icPtr;
    namePtr = Tcl_NewStringObj("hull", 4);
    Tcl_IncrRefCount(namePtr);
    if (ItclCreateComponent(interp, iclsPtr, namePtr, &icPtr) != TCL_OK) {
        return TCL_ERROR;
    }
    /* create the options variable */
    namePtr = Tcl_NewStringObj("itcl_options", 11);
    Tcl_IncrRefCount(namePtr);
    if (Itcl_CreateVariable(interp, iclsPtr, namePtr, NULL, NULL,
            &ivPtr) != TCL_OK) {
        return TCL_ERROR;
    }
    iclsPtr->numVariables++;
    Itcl_BuildVirtualTables(iclsPtr);
    return result;
}


/*
 * ------------------------------------------------------------------------
 *  Itcl_WidgetAdaptorCmd()
 *
 *  Used to an [incr Tcl] widgetadaptor
 *
 *  Returns TCL_OK/TCL_ERROR to indicate success/failure.
 * ------------------------------------------------------------------------
 */
/* ARGSUSED */
int
Itcl_WidgetAdaptorCmd(
    ClientData clientData,   /* infoPtr */
    Tcl_Interp *interp,      /* current interpreter */
    int objc,                /* number of arguments */
    Tcl_Obj *CONST objv[])   /* argument objects */
{
    Tcl_Obj *namePtr;
    ItclClass *iclsPtr;
    ItclObjectInfo *infoPtr;
    ItclComponent *icPtr;
    ItclVariable *ivPtr;
    int result;

    infoPtr = (ItclObjectInfo *)clientData;
    ItclShowArgs(0, "Itcl_WidgetAdaptorCmd", objc-1, objv);
    result = ItclClassBaseCmd(clientData, interp, ITCL_WIDGETADAPTOR,
            objc, objv, &iclsPtr);
    /* create the hull variable */
    namePtr = Tcl_NewStringObj("hull", 4);
    Tcl_IncrRefCount(namePtr);
    if (ItclCreateComponent(interp, iclsPtr, namePtr, &icPtr) != TCL_OK) {
        return TCL_ERROR;
    }
    iclsPtr->numVariables++;
    /* create the options variable */
    namePtr = Tcl_NewStringObj("itcl_options", 11);
    Tcl_IncrRefCount(namePtr);
    if (Itcl_CreateVariable(interp, iclsPtr, namePtr, NULL, NULL,
            &ivPtr) != TCL_OK) {
        return TCL_ERROR;
    }
    iclsPtr->numVariables++;
    Itcl_BuildVirtualTables(iclsPtr);
    return result;
}