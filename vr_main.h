#ifndef __VR_MAIN_H
#define __VR_MAIN_H

#include "pub_tool_basics.h"
#include "pub_tool_vki.h"
#include "pub_tool_debuginfo.h"
#include "pub_tool_libcbase.h"
#include "pub_tool_libcassert.h"
#include "pub_tool_libcfile.h"
#include "pub_tool_libcprint.h"
#include "pub_tool_libcproc.h"
#include "pub_tool_machine.h"
#include "pub_tool_mallocfree.h"
#include "pub_tool_options.h"
#include "pub_tool_oset.h"
#include "pub_tool_tooliface.h"
#include "pub_tool_xarray.h"
#include "pub_tool_clientstate.h"
#include "pub_tool_machine.h"
#include "pub_tool_stacktrace.h"
#include "pub_tool_threadstate.h"
#include "pub_tool_gdbserver.h"

#include "verrou.h"
#include "vr_fpOps.h"


// * Type declarations

typedef enum {
  VR_INSTR_OFF,
  VR_INSTR_ON,
  VR_INSTR
} Vr_Instr;

typedef enum {
  VR_OP_ADD,    // Addition
  VR_OP_SUB,    // Subtraction
  VR_OP_MUL,    // Multiplication
  VR_OP_DIV,    // Division
  VR_OP_MADD,   // FMA ADD
  VR_OP_MSUB,   // FMA SUB
  VR_OP
} Vr_Op;

typedef struct Vr_Exclude_ Vr_Exclude;
struct Vr_Exclude_ {
  HChar*      fnname;
  HChar*      objname;
  Bool        used;
  Vr_Exclude* next;
};

typedef struct {
  enum vr_RoundingMode roundingMode;
  Bool count;
  Bool instr_op[VR_OP];
  Bool instr_scalar;
  Vr_Instr instrument;
  Bool verbose;

  Bool genExclude;
  HChar * excludeFile;
  Vr_Exclude * exclude;
} Vr_State;

extern Vr_State vr;


// * Functions declarations

// ** vr_main.c

void vr_ppOpCount (void);


// ** vr_clreq.c

Bool vr_handle_client_request (ThreadId tid, UWord *args, UWord *ret);


// ** vr_error.c

typedef enum {
  VR_ERROR_UNCOUNTED,
  VR_ERROR_SCALAR,
  VR_ERROR
} Vr_ErrorKind;

const HChar* vr_get_error_name (Error* err);
Bool vr_recognised_suppression (const HChar* name, Supp* su);
void vr_before_pp_Error (Error* err) ;
void vr_pp_Error (Error* err);
Bool vr_eq_Error (VgRes res, Error* e1, Error* e2);
UInt vr_update_extra (Error* err);
Bool vr_error_matches_suppression (Error* err, Supp* su);
Bool vr_read_extra_suppression_info (Int fd, HChar** bufpp, SizeT* nBuf,
                                     Int* lineno, Supp* su);
Bool vr_print_extra_suppression_info (Error* er,
                                      /*OUT*/HChar* buf, Int nBuf);
Bool vr_print_extra_suppression_use (Supp* s,
                                     /*OUT*/HChar* buf, Int nBuf);
void vr_update_extra_suppression_use (Error* err, Supp* su);


void vr_maybe_record_ErrorOp (Vr_ErrorKind kind, IROp op);


// ** vr_exclude.c

Bool        vr_aboveFunction (HChar *ancestor, Addr * ips, UInt nips);
Vr_Exclude* vr_findExclude (Vr_Exclude* list, HChar * fnname, HChar * objname);
Vr_Exclude* vr_addExclude (Vr_Exclude* list, HChar * fnname, HChar * objname);
void        vr_freeExcludeList (Vr_Exclude* list);
void        vr_dumpExcludeList (Vr_Exclude * list, HChar * filename);
Vr_Exclude* vr_loadExcludeList (Vr_Exclude * list, HChar * filename);
Bool        vr_excludeIRSB(Vr_Exclude ** list, Bool generate);


// ** vr_clo.c

void vr_clo_defaults (void);
Bool vr_process_clo (const HChar *arg);
void vr_print_usage (void);
void vr_print_debug_usage (void);


#endif /*ndef __VR_MAIN_H*/