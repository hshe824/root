/*****************************************************************************
 * Project: BaBar detector at the SLAC PEP-II B-factory
 * Package: RooFitTools
 *    File: $Id: RooProdPdf.rdl,v 1.23 2002/08/21 23:06:29 verkerke Exp $
 * Authors:
 *   DK, David Kirkby, Stanford University, kirkby@hep.stanford.edu
 *   WV, Wouter Verkerke, UC Santa Barbara, verkerke@slac.stanford.edu
 * History:
 *   06-Jan-2000 DK Created initial version
 *   19-Apr-2000 DK Add the printEventStats() method
 *   26-Jun-2000 DK Add support for extended likelihood fits
 *   02-Jul-2000 DK Add support for multiple terms (instead of only 2)
 *   05-Jul-2000 DK Add support for extended maximum likelihood and a
 *                  new method for this: setNPar()
 *   03-May02001 WV Port to RooFitCore/RooFitModels
 *
 * Copyright (C) 2000 Stanford University
 *****************************************************************************/
#ifndef ROO_PROD_PDF
#define ROO_PROD_PDF

#include "RooFitCore/RooAbsPdf.hh"
#include "RooFitCore/RooListProxy.hh"
#include "RooFitCore/RooAICRegistry.hh"
#include "RooFitCore/RooNormListManager.hh"

class RooProdPdf : public RooAbsPdf {
public:
  RooProdPdf(const char *name, const char *title, Double_t cutOff=0);
  RooProdPdf(const char *name, const char *title,
	    RooAbsPdf& pdf1, RooAbsPdf& pdf2, Double_t cutOff=0) ;
  RooProdPdf(const char* name, const char* title, const RooArgList& pdfList, Double_t cutOff=0) ;
  RooProdPdf(const RooProdPdf& other, const char* name=0) ;
  virtual TObject* clone(const char* newname) const { return new RooProdPdf(*this,newname) ; }
  virtual ~RooProdPdf() ;

  Double_t evaluate() const ;
  virtual Bool_t checkDependents(const RooArgSet* nset) const ;	

  virtual Bool_t forceAnalyticalInt(const RooAbsArg& dep) const { return kTRUE ; }
  Int_t getAnalyticalIntegralWN(RooArgSet& allVars, RooArgSet& numVars, const RooArgSet* normSet) const ;
  Double_t analyticalIntegralWN(Int_t code, const RooArgSet* normSet) const ;
  virtual Bool_t selfNormalized() const { return kTRUE ; }

  virtual ExtendMode extendMode() const ;
  virtual Double_t expectedEvents() const ; 

  const RooArgList& pdfList() const { return _pdfList ; }

protected:

  Double_t calculate(const RooArgList* partIntList, const RooArgList* codList) const ;
  Double_t calculate(const RooArgList* partIntList) const ;
  void getPartIntList(const RooArgSet* nset, const RooArgSet* iset, Int_t& code, 
		      RooArgList*& part1List, RooArgList*& part2List, 
		      RooArgList*& cod1List,  RooArgList*& cod2List) const ;
  RooArgList* getCategoryOverlapDeps(const RooArgSet* depSet) const ;
  
  mutable RooNormListManager _part1ListMgr ; // Partial normalization list manager
  mutable RooNormListManager _part2ListMgr ; // Partial normalization list manager
  mutable RooNormListManager _cod1ListMgr ; // Partial normalization list manager
  mutable RooNormListManager _cod2ListMgr ; // Partial normalization list manager
  
  virtual Bool_t redirectServersHook(const RooAbsCollection& newServerList, Bool_t mustReplaceAll, Bool_t nameChange) ;

  friend class RooProdGenContext ;
  virtual RooAbsGenContext* genContext(const RooArgSet &vars, 
				       const RooDataSet *prototype=0, Bool_t verbose= kFALSE) const ;

  mutable RooAICRegistry _codeReg ; // Registry of component analytical integration codes

  Double_t _cutOff ;       //  Cutoff parameter for running product
  RooListProxy _pdfList ;  //  List of PDF components
  mutable RooListProxy _partList ; //  Partial integrals du jour
  TIterator* _pdfIter ;    //! Iterator of PDF list
  Int_t _extendedIndex ;   //  Index of extended PDF (if any) 

private:

  ClassDef(RooProdPdf,0) // PDF representing a product of PDFs
};

#endif
