#-- start of make_header -----------------

#====================================
#  Library DD
#
#   Generated Wed Sep  7 11:01:04 2016  by suym
#
#====================================

include ${CMTROOT}/src/Makefile.core

ifdef tag
CMTEXTRATAGS = $(tag)
else
tag       = $(CMTCONFIG)
endif

cmt_DD_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_DD_has_target_tag

tags      = $(tag),$(CMTEXTRATAGS),target_DD

DDAlg_tag = $(tag)

ifdef READONLY
cmt_local_tagfile_DD = /tmp/CMT_$(DDAlg_tag)_DD.make$(cmt_lock_pid)
else
#cmt_local_tagfile_DD = $(DDAlg_tag)_DD.make
cmt_local_tagfile_DD = $(bin)$(DDAlg_tag)_DD.make
endif

else

tags      = $(tag),$(CMTEXTRATAGS)

DDAlg_tag = $(tag)

ifdef READONLY
cmt_local_tagfile_DD = /tmp/CMT_$(DDAlg_tag).make$(cmt_lock_pid)
else
#cmt_local_tagfile_DD = $(DDAlg_tag).make
cmt_local_tagfile_DD = $(bin)$(DDAlg_tag).make
endif

endif

-include $(cmt_local_tagfile_DD)

ifdef cmt_DD_has_target_tag

ifdef READONLY
cmt_final_setup_DD = /tmp/CMT_DDAlg_DDsetup.make
cmt_local_DD_makefile = /tmp/CMT_DD$(cmt_lock_pid).make
else
cmt_final_setup_DD = $(bin)DDAlg_DDsetup.make
cmt_local_DD_makefile = $(bin)DD.make
endif

else

ifdef READONLY
cmt_final_setup_DD = /tmp/CMT_DDAlgsetup.make
cmt_local_DD_makefile = /tmp/CMT_DD$(cmt_lock_pid).make
else
cmt_final_setup_DD = $(bin)DDAlgsetup.make
cmt_local_DD_makefile = $(bin)DD.make
endif

endif

ifdef READONLY
cmt_final_setup = /tmp/CMT_DDAlgsetup.make
else
cmt_final_setup = $(bin)DDAlgsetup.make
endif

DD ::


ifdef READONLY
DD ::
	@echo tags=$(tags)
	@echo cmt_local_tagfile=$(cmt_local_tagfile)
endif


dirs ::
	@if test ! -r requirements ; then echo "No requirements file" ; fi; \
	  if test ! -d $(bin) ; then $(mkdir) -p $(bin) ; fi

javadirs ::
	@if test ! -d $(javabin) ; then $(mkdir) -p $(javabin) ; fi

srcdirs ::
	@if test ! -d $(src) ; then $(mkdir) -p $(src) ; fi

help ::
	$(echo) 'DD'

binobj = 
ifdef STRUCTURED_OUTPUT
binobj = DD/
DD::
	@if test ! -d $(bin)$(binobj) ; then $(mkdir) -p $(bin)$(binobj) ; fi
	$(echo) "STRUCTURED_OUTPUT="$(bin)$(binobj)
endif

#-- end of make_header ------------------

#-- start of libary_header ---------------

DDlibname   = $(bin)$(library_prefix)DD$(library_suffix)
DDlib       = $(DDlibname).a
DDstamp     = $(bin)DD.stamp
DDshstamp   = $(bin)DD.shstamp

DD :: dirs  DDLIB
	$(echo) "DD ok"

#-- end of libary_header ----------------

DDLIB :: $(DDlib) $(DDshstamp)
	@/bin/echo "------> DD : library ok"

$(DDlib) :: $(bin)DD.o
	$(lib_echo) library
	$(lib_silent) cd $(bin); \
	  $(ar) $(DDlib) $?
	$(lib_silent) $(ranlib) $(DDlib)
	$(lib_silent) cat /dev/null >$(DDstamp)

#------------------------------------------------------------------
#  Future improvement? to empty the object files after
#  storing in the library
#
##	  for f in $?; do \
##	    rm $${f}; touch $${f}; \
##	  done
#------------------------------------------------------------------

$(DDlibname).$(shlibsuffix) :: $(DDlib) $(DDstamps)
	$(lib_silent) cd $(bin); QUIET=$(QUIET); $(make_shlib) "$(tags)" DD $(DD_shlibflags)

$(DDshstamp) :: $(DDlibname).$(shlibsuffix)
	@if test -f $(DDlibname).$(shlibsuffix) ; then cat /dev/null >$(DDshstamp) ; fi

DDclean ::
	$(cleanup_echo) objects
	$(cleanup_silent) cd $(bin); /bin/rm -f $(bin)DD.o

#-----------------------------------------------------------------
#
#  New section for automatic installation
#
#-----------------------------------------------------------------

ifeq ($(INSTALLAREA),)
installarea = $(CMTINSTALLAREA)
else
ifeq ($(findstring `,$(INSTALLAREA)),`)
installarea = $(shell $(subst `,, $(INSTALLAREA)))
else
installarea = $(INSTALLAREA)
endif
endif

install_dir = ${installarea}/${CMTCONFIG}/lib
DDinstallname = $(library_prefix)DD$(library_suffix).$(shlibsuffix)

DD :: DDinstall

install :: DDinstall

DDinstall :: $(install_dir)/$(DDinstallname)
	@if test ! "${installarea}" = ""; then\
	  echo "installation done"; \
	fi

$(install_dir)/$(DDinstallname) :: $(bin)$(DDinstallname)
	@if test ! "${installarea}" = ""; then \
	  cd $(bin); \
	  if test ! "$(install_dir)" = ""; then \
	    if test ! -d "$(install_dir)"; then \
	      mkdir -p $(install_dir); \
	    fi ; \
	    if test -d "$(install_dir)"; then \
	      echo "Installing library $(DDinstallname) into $(install_dir)"; \
	      if test -e $(install_dir)/$(DDinstallname); then \
	        $(cmt_uninstall_area_command) $(install_dir)/$(DDinstallname); \
	        $(cmt_uninstall_area_command) $(install_dir)/$(DDinstallname).cmtref; \
	      fi; \
	      $(cmt_install_area_command) `pwd`/$(DDinstallname) $(install_dir)/$(DDinstallname); \
	      echo `pwd`/$(DDinstallname) >$(install_dir)/$(DDinstallname).cmtref; \
	    fi \
          else \
	    echo "Cannot install library $(DDinstallname), no installation directory specified"; \
	  fi; \
	fi

DDclean :: DDuninstall

uninstall :: DDuninstall

DDuninstall ::
	@if test ! "${installarea}" = ""; then \
	  cd $(bin); \
	  if test ! "$(install_dir)" = ""; then \
	    if test -d "$(install_dir)"; then \
	      echo "Removing installed library $(DDinstallname) from $(install_dir)"; \
	      $(cmt_uninstall_area_command) $(install_dir)/$(DDinstallname); \
	      $(cmt_uninstall_area_command) $(install_dir)/$(DDinstallname).cmtref; \
	    fi \
          else \
	    echo "Cannot uninstall library $(DDinstallname), no installation directory specified"; \
	  fi; \
	fi




#-- start of dependency ------------------
ifneq ($(MAKECMDGOALS),DDclean)

#$(bin)DD_dependencies.make :: dirs

ifndef QUICK
$(bin)DD_dependencies.make : ../src/DD.cxx $(use_requirements) $(cmt_final_setup_DD)
	$(echo) "(DD.make) Rebuilding $@"; \
	  $(build_dependencies) DD -all_sources -out=$@ ../src/DD.cxx
endif

#$(DD_dependencies)

-include $(bin)DD_dependencies.make

endif
#-- end of dependency -------------------
#-- start of cpp_library -----------------

$(bin)DD_dependencies.make : $(DD_cxx_dependencies)

$(bin)$(binobj)DD.o : $(DD_cxx_dependencies)
	$(cpp_echo) $(src)DD.cxx
	$(cpp_silent) $(cppcomp) -o $(@) $(use_pp_cppflags) $(DD_pp_cppflags) $(lib_DD_pp_cppflags) $(DD_pp_cppflags) $(use_cppflags) $(DD_cppflags) $(lib_DD_cppflags) $(DD_cppflags) $(DD_cxx_cppflags)  $(src)DD.cxx

#-- end of cpp_library ------------------
#-- start of cleanup_header --------------

clean :: DDclean
	@cd .

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(DD.make) $@: No rule for such target" >&2
#	@echo "#CMT> Warning: $@: No rule for such target" >&2; exit
else
.DEFAULT::
	$(echo) "(DD.make) PEDANTIC: $@: No rule for such target" >&2
	if test $@ = "$(cmt_final_setup)" -o\
	 $@ = "$(cmt_final_setup_DD)" ; then\
	 found=n; for s in 1 2 3 4 5; do\
	 sleep $$s; test ! -f $@ || { found=y; break; }\
	 done; if test $$found = n; then\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(DD.make) PEDANTIC: $@: Seems to be missing. Ignore it for now" >&2; exit 0 ; fi;\
	 elif test `expr index $@ '/'` -ne 0 ; then\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(DD.make) PEDANTIC: $@: Seems to be a missing file. Please check" >&2; exit 2 ; \
	 else\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(DD.make) PEDANTIC: $@: Seems to be a fake target due to some pattern. Just ignore it" >&2 ; exit 0; fi
endif

DDclean ::
#-- end of cleanup_header ---------------
#-- start of cleanup_library -------------
	$(cleanup_echo) library
	-$(cleanup_silent) cd $(bin); /bin/rm -f $(binobj)$(library_prefix)DD$(library_suffix).a $(binobj)$(library_prefix)DD$(library_suffix).s? $(binobj)DD.stamp $(binobj)DD.shstamp
#-- end of cleanup_library ---------------

