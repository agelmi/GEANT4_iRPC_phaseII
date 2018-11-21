#! /usr/bin/python								#per renderlo esguibile
# -*- coding: utf-8 -*-					#per poter usare caratteri speciali come _

import math										#importa la libreria matematica
import string										#importa la libreria stringhe
import glob



#librerie pyROOT per disegnare grafici
import ROOT
from ROOT import gROOT
from ROOT import TCanvas, TGraph, gPad, TF1, TF2 , kRed, TMultiGraph, TLegend, gStyle, TPaveStats, TStyle, TText, TList, TLatex, TMath, TFormula, TGraphErrors, TTree, TDatime, TMath
from ROOT import TCanvas, TGraph, gPad, TF1, kRed, TMultiGraph, TLegend, gStyle, TPaveStats, TStyle, TText, TList, TLatex, TMultiGraph, TH1F, TFile
from array import array

spazio="	"

#script per estrarre in automatico i valori di sensitività (a specifico valore di energia) dai file root 

file_out=open("sensitivity_out_extracted.csv", "w")		#crea file output con valori sensistività estratti da ogni rootfile
intestazione="energy sensitivity_% PDGcode \n"				#intestazione file out
file_out.write(intestazione)

list_rootfile= glob.glob('*.root') 						#lista file root da cui prendere grafici


for rootfile in list_rootfile:							#loop su ogni rootfile
	input_root = TFile(rootfile)							#apre root file

	#prende valore energia
	imported_tree= input_root.Get("p_incident_TOT")		#prende ttree
	imported_tree.Draw("KINETIC_ENERGY_TOT","","")	#disegna plot da ttree per poter prendere e modificare
	histo= imported_tree.GetHistogram().Clone()
	mean_energy=histo.GetMean()

	#prende PDG CODE
	imported_tree.Draw("PARTICLE_DATA_GROUP_TOT","","")	#disegna plot da ttree per poter prendere e modificare
	histo= imported_tree.GetHistogram().Clone()
	PDG=histo.GetMean()

	#prende valore sensitività	
	sensitivity_h= input_root.Get("sensitivity")		#prende grafico sensitivity (se c'è)

	if sensitivity_h:					#se c'è grafico sensitivity estrae valore
		mean= sensitivity_h.GetMean()
		xbin=sensitivity_h.GetXaxis().FindBin(mean)
		sensitivity= sensitivity_h.GetBinContent(xbin)
	else:							#se non c'è grafico sensitivity la mette a 0
		sensitivity=0
		

	#scrive su file
	dati= str(mean_energy) +spazio+ str(sensitivity)+spazio+ str(PDG)+"\n"
	file_out.write(dati)














