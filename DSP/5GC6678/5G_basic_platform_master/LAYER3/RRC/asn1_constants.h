#define maxBandComb                             65536   // Maximum number of DL band combinations
#define maxCellBlack                            16      // Maximum number of NR blacklisted cell ranges in SIB3, SIB4
#define maxCellInter                            16      // Maximum number of inter_Freq cells listed in SIB4
#define maxCellIntra                            16      // Maximum number of intra_Freq cells listed in SIB3
#define maxCellMeasEUTRA                        32      // Maximum number of cells in E_UTRAN
#define maxEARFCN                               262143  // Maximum value of E_UTRA carrier frequency
#define maxEUTRA_CellBlack                      16      // Maximum number of E_UTRA blacklisted physical cell identity ranges
                                                            // in SIB5
#define maxEUTRA_NS_Pmax                        8       // Maximum number of NS and P_Max values per band
#define maxMultiBands                           8       // Maximum number of additional frequency bands that a cell belongs to
#define maxNARFCN                               3279165 // Maximum value of NR carrier frequency
#define maxNR_NS_Pmax                           8       // Maximum number of NS and P_Max values per band
#define maxNrofServingCells                     32      // Max number of serving cells (SpCells + SCells)
#define maxNrofServingCells_1                   31      // Max number of serving cells (SpCell + SCells) per cell group
#define maxNrofAggregatedCellsPerCellGroup      16
#define maxNrofSCells                           31      // Max number of secondary serving cells per cell group
#define maxNrofCellMeas                         32      // Maximum number of entries in each of the cell lists in a measurement
                                                            // object
#define maxNrofSS_BlocksToAverage               16      // Max number for the (max) number of SS blocks to average to determine cell
                                                            // measurement
#define maxNrofCSI_RS_ResourcesToAverage        16      // Max number for the (max) number of CSI_RS to average to determine cell
                                                            // measurement
#define maxNrofDL_Allocations                   16      // Maximum number of PDSCH time domain resource allocations
#define maxNrofSR_ConfigPerCellGroup            8       // Maximum number of SR configurations per cell group
#define maxLCG_ID                               7       // Maximum value of LCG ID
#define maxLC_ID                                32      // Maximum value of Logical Channel ID
#define maxNrofTAGs                             4       // Maximum number of Timing Advance Groups
#define maxNrofTAGs_1                           3       // Maximum number of Timing Advance Groups minus 1
#define maxNrofBWPs                             4       // Maximum number of BWPs per serving cell
#define maxNrofCombIDC                          128     // Maximum number of reported MR_DC combinations for IDC
#define maxNrofSymbols_1                        13      // Maximum index identifying a symbol within a slot (14 symbols, indexed
                                                            // from 0..13)
#define maxNrofSlots                            320     // Maximum number of slots in a 10 ms period
#define maxNrofSlots_1                          319     // Maximum number of slots in a 10 ms period minus 1
#define maxNrofPhysicalResourceBlocks           275     // Maximum number of PRBs
#define maxNrofPhysicalResourceBlocks_1         274     // Maximum number of PRBs minus 1
#define maxNrofPhysicalResourceBlocksPlus1      276     // Maximum number of PRBs plus 1
#define maxNrofControlResourceSets_1            11      // Max number of CoReSets configurable on a serving cell minus 1
#define maxCoReSetDuration                      3       // Max number of OFDM symbols in a control resource set
#define maxNrofSearchSpaces_1                   39      // Max number of Search Spaces minus 1
#define maxSFI_DCI_PayloadSize                  128     // Max number payload of a DCI scrambled with SFI_RNTI
#define maxSFI_DCI_PayloadSize_1                127     // Max number payload of a DCI scrambled with SFI_RNTI minus 1
#define maxINT_DCI_PayloadSize                  126     // Max number payload of a DCI scrambled with INT_RNTI
#define maxINT_DCI_PayloadSize_1                125     // Max number payload of a DCI scrambled with INT_RNTI minus 1
#define maxNrofRateMatchPatterns                4       // Max number of rate matching patterns that may be configured
#define maxNrofRateMatchPatterns_1              3       // Max number of rate matching patterns that may be configured minus 1
#define maxNrofRateMatchPatternsPerGroup        8       // Max number of rate matching patterns that may be configured in one group
#define maxNrofCSI_ReportConfigurations         48      // Maximum number of report configurations
#define maxNrofCSI_ReportConfigurations_1       47      // Maximum number of report configurations minus 1
#define maxNrofCSI_ResourceConfigurations       112     // Maximum number of resource configurations
#define maxNrofCSI_ResourceConfigurations_1     111     // Maximum number of resource configurations minus 1
#define maxNrofAP_CSI_RS_ResourcesPerSet        16
#define maxNrOfCSI_AperiodicTriggers            128     // Maximum number of triggers for aperiodic CSI reporting
#define maxNrofReportConfigPerAperiodicTrigger  16      // Maximum number of report configurations per trigger state for aperiodic
                                                            // reporting
#define maxNrofNZP_CSI_RS_Resources             192     // Maximum number of Non_Zero_Power (NZP) CSI_RS resources
#define maxNrofNZP_CSI_RS_Resources_1           191     // Maximum number of Non_Zero_Power (NZP) CSI_RS resources minus 1
#define maxNrofNZP_CSI_RS_ResourcesPerSet       64      // Maximum number of NZP CSI_RS resources per resource set
#define maxNrofNZP_CSI_RS_ResourceSets          64      // Maximum number of NZP CSI_RS resources per cell
#define maxNrofNZP_CSI_RS_ResourceSets_1        63      // Maximum number of NZP CSI_RS resources per cell minus 1
#define maxNrofNZP_CSI_RS_ResourceSetsPerConfig 16      // Maximum number of resource sets per resource configuration
#define maxNrofNZP_CSI_RS_ResourcesPerConfig    128     // Maximum number of resources per resource configuration
#define maxNrofZP_CSI_RS_Resources              32      // Maximum number of Zero_Power (ZP) CSI_RS resources
#define maxNrofZP_CSI_RS_Resources_1            31      // Maximum number of Zero_Power (ZP) CSI_RS resources minus 1
#define maxNrofZP_CSI_RS_ResourceSets_1         15
#define maxNrofZP_CSI_RS_ResourcesPerSet        16
#define maxNrofZP_CSI_RS_ResourceSets           16
#define maxNrofCSI_IM_Resources                 32      // Maximum number of CSI_IM resources. See CSI_IM_ResourceMax in 38.214.
#define maxNrofCSI_IM_Resources_1               31      // Maximum number of CSI_IM resources minus 1. See CSI_IM_ResourceMax
                                                            // in 38.214.
#define maxNrofCSI_IM_ResourcesPerSet           8       // Maximum number of CSI_IM resources per set. See CSI_IM_ResourcePerSetMax
                                                            // in 38.214
#define maxNrofCSI_IM_ResourceSets              64      // Maximum number of NZP CSI_IM resources per cell
#define maxNrofCSI_IM_ResourceSets_1            63      // Maximum number of NZP CSI_IM resources per cell minus 1
#define maxNrofCSI_IM_ResourceSetsPerConfig     16      // Maximum number of CSI IM resource sets per resource configuration
#define maxNrofCSI_SSB_ResourcePerSet           64      // Maximum number of SSB resources in a resource set
#define maxNrofCSI_SSB_ResourceSets             64      // Maximum number of CSI SSB resource sets per cell
#define maxNrofCSI_SSB_ResourceSets_1           63      // Maximum number of CSI SSB resource sets per cell minus 1
#define maxNrofCSI_SSB_ResourceSetsPerConfig    1       // Maximum number of CSI SSB resource sets per resource configuration
#define maxNrofFailureDetectionResources        10      // Maximum number of failure detection resources
#define maxNrofFailureDetectionResources_1      9       // Maximum number of failure detection resources minus 1
#define maxNrofObjectId                         64      // Maximum number of measurement objects
#define maxNrofPageRec                          32      // Maximum number of page records
#define maxNrofPCI_Ranges                       8       // Maximum number of PCI ranges
#define maxPLMN                                 12      // Maximum number of PLMNs broadcast and reported by UE at establisghment
#define maxNrofCSI_RS_ResourcesRRM              96      // Maximum number of CSI_RS resources for an RRM measurement object
#define maxNrofCSI_RS_ResourcesRRM_1            95      // Maximum number of CSI_RS resources for an RRM measurement object minus 1
#define maxNrofMeasId                           64      // Maximum number of configured measurements
#define maxNrofQuantityConfig                   2       // Maximum number of quantity configurations
#define maxNrofCSI_RS_CellsRRM                  96      // Maximum number of cells with CSI_RS resources for an RRM measurement
                                                            // object
#define maxNrofSRS_ResourceSets                 16      // Maximum number of SRS resource sets in a BWP.
#define maxNrofSRS_ResourceSets_1               15      // Maximum number of SRS resource sets in a BWP minus 1.
#define maxNrofSRS_Resources                    64      // Maximum number of SRS resources.
#define maxNrofSRS_Resources_1                  63      // Maximum number of SRS resources in an SRS resource set minus 1.
#define maxNrofSRS_ResourcesPerSet              16      // Maximum number of SRS resources in an SRS resource set
#define maxNrofSRS_TriggerStates_1              3       // Maximum number of SRS trigger states minus 1, i.e., the largest code
                                                            // point.
#define maxNrofSRS_TriggerStates_2              2       // Maximum number of SRS trigger states minus 2.
#define maxRAT_CapabilityContainers             8       // Maximum number of interworking RAT containers (incl NR and MRDC)
#define maxSimultaneousBands                    32      // Maximum number of simultaneously aggregated bands
#define maxNrofSlotFormatCombinationsPerSet     512     // Maximum number of Slot Format Combinations in a SF_Set.
#define maxNrofSlotFormatCombinationsPerSet_1   511     // Maximum number of Slot Format Combinations in a SF_Set minus 1.
#define maxNrofPUCCH_Resources                  128
#define maxNrofPUCCH_Resources_1                127
#define maxNrofPUCCH_ResourceSets               4       // Maximum number of PUCCH Resource Sets
#define maxNrofPUCCH_ResourceSets_1             3       // Maximum number of PUCCH Resource Sets minus 1.
#define maxNrofPUCCH_ResourcesPerSet            32      // Maximum number of PUCCH Resources per PUCCH_Resour©ceSet
#define maxNrofPUCCH_P0_PerSet                  8       // Maximum number of P0_pucch present in a p0_pucch set
#define maxNrofPUCCH_PathlossReferenceRSs       4       // Maximum number of RSs used as pathloss reference for PUCCH power control.
#define maxNrofPUCCH_PathlossReferenceRSs_1     3       // Maximum number of RSs used as pathloss reference for PUCCH power
                                                            // control minus 1.
#define maxNrofP0_PUSCH_AlphaSets               30      // Maximum number of P0_pusch_alpha_sets (see 38,213, clause 7.1)
#define maxNrofP0_PUSCH_AlphaSets_1             29      // Maximum number of P0_pusch_alpha_sets minus 1 (see 38,213, clause 7.1)
#define maxNrofPUSCH_PathlossReferenceRSs       4       // Maximum number of RSs used as pathloss reference for PUSCH power control.
#define maxNrofPUSCH_PathlossReferenceRSs_1     3       // Maximum number of RSs used as pathloss reference for PUSCH power
                                                            // control minus 1.
#define maxNrofNAICS_Entries                    8       // Maximum number of supported NAICS capability set
#define maxBands                                1024    // Maximum number of supported bands in UE capability.
#define maxBandsMRDC                            1280
#define maxBandsEUTRA                           256
#define maxCellReport                           8
#define maxDRB                                  29      // Maximum number of DRBs (that can be added in DRB_ToAddModLIst).
#define maxFreq                                 8       // Max number of frequencies.
#define maxFreqIDC_MRDC                         32      // Maximum number of candidate NR frequencies for MR_DC IDC indication
#define maxNrofCandidateBeams                   16      // Max number of PRACH_ResourceDedicatedBFR that in BFR config.
#define maxNrofPCIsPerSMTC                      64      // Maximun number of PCIs per SMTC.
#define maxNrofQFIs                             64
#define maxNrOfSemiPersistentPUSCH_Triggers     64      // Maximum number of triggers for semi persistent reporting on PUSCH
#define maxNrofSR_Resources                     8       // Maximum number of SR resources per BWP in a cell.
#define maxNrofSlotFormatsPerCombination        256
#define maxNrofSpatialRelationInfos             8
#define maxNrofIndexesToReport                  32
#define maxNrofIndexesToReport2                 64
#define maxNrofSSBs_1                           63      // Maximum number of SSB resources in a resource set minus 1.
#define maxNrofS_NSSAI                          8       // Maximum number of S_NSSAI.
#define maxNrofTCI_StatesPDCCH                  64
#define maxNrofTCI_States                       128     // Maximum number of TCI states.
#define maxNrofTCI_States_1                     127     // Maximum number of TCI states minus 1.
#define maxNrofUL_Allocations                   16      // Maximum number of PUSCH time domain resource allocations.
#define maxQFI                                  63
#define maxRA_CSIRS_Resources                   96
#define maxRA_OccasionsPerCSIRS                 64      // Maximum number of RA occasions for one CSI_RS
#define maxRA_Occasions_1                       511     // Maximum number of RA occasions in the system
#define maxRA_SSB_Resources                     64
#define maxSCSs                                 5
#define maxSecondaryCellGroups                  3
#define maxNrofServingCellsEUTRA                32
#define maxMBSFN_Allocations                    8
#define maxNrofMultiBands                       8
#define maxCellSFTD                             3       // Maximum number of cells for SFTD reporting
#define maxReportConfigId                       64
#define maxNrofCodebooks                        16      // Maximum number of codebooks suppoted by the UE
#define maxNrofCSI_RS_Resources                 7       // Maximum number of codebook resources supported by the UE
#define maxNrofSRI_PUSCH_Mappings               16
#define maxNrofSRI_PUSCH_Mappings_1             15
#define maxSIB                                  32       // Maximum number of SIBs
#define maxSI_Message                           32       // Maximum number of SI messages
#define maxPO_perPF                             4       // Maximum number of paging occasion per paging frame
#define maxAccessCat_1                          63      // Maximum number of Access Categories minus 1
#define maxBarringInfoSet                       8       // Maximum number of Access Categories
#define maxCellEUTRA                            8       // Maximum number of E_UTRA cells in SIB list
#define maxEUTRA_Carrier                        8       // Maximum number of E_UTRA carriers in SIB list
#define maxPLMNIdentities                       8       // Maximum number of PLMN identites in RAN area configurations
#define maxDownlinkFeatureSets                  1024    // (for NR DL) Total number of FeatureSets (size of the pool)
#define maxUplinkFeatureSets                    1024    // (for NR UL) Total number of FeatureSets (size of the pool)
#define maxEUTRA_DL_FeatureSets                 256     // (for E_UTRA) Total number of FeatureSets (size of the pool)
#define maxEUTRA_UL_FeatureSets                 256     // (for E_UTRA) Total number of FeatureSets (size of the pool)
#define maxFeatureSetsPerBand                   128     // (for NR) The number of feature sets associated with one band.
#define maxPerCC_FeatureSets                    1024    // (for NR) Total number of CC_specific FeatureSets (size of the pool)
#define maxFeatureSetCombinations               1024    // (for MR_DC/NR)Total number of Feature set combinations (size of the
                                                            // pool)
#define maxInterRAT_RSTD_Freq                   3
