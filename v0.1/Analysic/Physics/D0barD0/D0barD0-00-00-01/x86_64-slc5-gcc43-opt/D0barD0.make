#-- start of make_header -----------------

#====================================
#  Library D0barD0
#
#   Generated Sat Sep  3 19:10:32 2016  by suym
#
#====================================

include ${CMTROOT}/src/Makefile.core

ifdef tag
CMTEXTRATAGS = $(tag)
else
tag       = $(CMTCONFIG)
endif

cmt_D0barD0_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_D0barD0_has_target_tag

tags      = $(tag),$(CMTEXTRATAGS),target_D0barD0

D0barD0_tag = $(tag)

ifdef READONLY
cmt_local_tagfile_D0barD0 = /tmp/CMT_$(D0barD0_tag)_D0barD0.make$(cmt_lock_pid)
else
#cmt_local_tagfile_D0barD0 = $(D0barD0_tag)_D0barD0.make
cmt_local_tagfile_D0barD0 = $(bin)$(D0barD0_tag)_D0barD0.make
endif

else

tags      = $(tag),$(CMTEXTRATAGS)

D0barD0_tag = $(tag)

ifdef READONLY
cmt_local_tagfile_D0barD0 = /tmp/CMT_$(D0barD0_tag).make$(cmt_lock_pid)
else
#cmt_local_tagfile_D0barD0 = $(D0barD0_tag).make
cmt_local_tagfile_D0barD0 = $(bin)$(D0barD0_tag).make
endif

endif

-include $(cmt_local_tagfile_D0barD0)

ifdef cmt_D0barD0_has_target_tag

ifdef READONLY
cmt_final_setup_D0barD0 = /tmp/CMT_D0barD0_D0barD0setup.make
cmt_local_D0barD0_makefile = /tmp/CMT_D0barD0$(cmt_lock_pid).make
else
cmt_final_setup_D0barD0 = $(bin)D0barD0_D0barD0setup.make
cmt_local_D0barD0_makefile = $(bin)D0barD0.make
endif

else

ifdef READONLY
cmt_final_setup_D0barD0 = /tmp/CMT_D0barD0setup.make
cmt_local_D0barD0_makefile = /tmp/CMT_D0barD0$(cmt_lock_pid).make
else
cmt_final_setup_D0barD0 = $(bin)D0barD0setup.make
cmt_local_D0barD0_makefile = $(bin)D0barD0.make
endif

endif

ifdef READONLY
cmt_final_setup = /tmp/CMT_D0barD0setup.make
else
cmt_final_setup = $(bin)D0barD0setup.make
endif

D0barD0 ::


ifdef READONLY
D0barD0 ::
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
	$(echo) 'D0barD0'

binobj = 
ifdef STRUCTURED_OUTPUT
binobj = D0barD0/
D0barD0::
	@if test ! -d $(bin)$(binobj) ; then $(mkdir) -p $(bin)$(binobj) ; fi
	$(echo) "STRUCTURED_OUTPUT="$(bin)$(binobj)
endif

#-- end of make_header ------------------

#-- start of libary_header ---------------

D0barD0libname   = $(bin)$(library_prefix)D0barD0$(library_suffix)
D0barD0lib       = $(D0barD0libname).a
D0barD0stamp     = $(bin)D0barD0.stamp
D0barD0shstamp   = $(bin)D0barD0.shstamp

D0barD0 :: dirs  D0barD0LIB
	$(echo) "D0barD0 ok"

#-- end of libary_header ----------------

D0barD0LIB :: $(D0barD0lib) $(D0barD0shstamp)
	@/bin/echo "------> D0barD0 : library ok"

$(D0barD0lib) :: $(bin)D0barD0.o
	$(lib_echo) library
	$(lib_silent) cd $(bin); \
	  $(ar) $(D0barD0lib) $?
	$(lib_silent) $(ranlib) $(D0barD0lib)
	$(lib_silent) cat /dev/null >$(D0barD0stamp)

#------------------------------------------------------------------
#  Future improvement? to empty the object files after
#  storing in the library
#
##	  for f in $?; do \
##	    rm $${f}; touch $${f}; \
##	  done
#------------------------------------------------------------------

$(D0barD0libname).$(shlibsuffix) :: $(D0barD0lib) $(D0barD0stamps)
	$(lib_silent) cd $(bin); QUIET=$(QUIET); $(make_shlib) "$(tags)" D0barD0 $(D0barD0_shlibflags)

$(D0barD0shstamp) :: $(D0barD0libname).$(shlibsuffix)
	@if test -f $(D0barD0libname).$(shlibsuffix) ; then cat /dev/null >$(D0barD0shstamp) ; fi

D0barD0clean ::
	$(cleanup_echo) objects
	$(cleanup_silent) cd $(bin); /bin/rm -f $(bin)D0barD0.o

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
D0barD0installname = $(library_prefix)D0barD0$(library_suffix).$(shlibsuffix)

D0barD0 :: D0barD0install

install :: D0barD0install

D0barD0install :: $(install_dir)/$(D0barD0installname)
	@if test ! "${installarea}" = ""; then\
	  echo "installation done"; \
	fi

$(install_dir)/$(D0barD0installname) :: $(bin)$(D0barD0installname)
	@if test ! "${installarea}" = ""; then \
	  cd $(bin); \
	  if test ! "$(install_dir)" = ""; then \
	    if test ! -d "$(install_dir)"; then \
	      mkdir -p $(install_dir); \
	    fi ; \
	    if test -d "$(install_dir)"; then \
	      echo "Installing library $(D0barD0installname) into $(install_dir)"; \
	      if test -e $(install_dir)/$(D0barD0installname); then \
	        $(cmt_uninstall_area_command) $(install_dir)/$(D0barD0installname); \
	        $(cmt_uninstall_area_command) $(install_dir)/$(D0barD0installname).cmtref; \
	      fi; \
	      $(cmt_install_area_command) `pwd`/$(D0barD0installname) $(install_dir)/$(D0barD0installname); \
	      echo `pwd`/$(D0barD0installname) >$(install_dir)/$(D0barD0installname).cmtref; \
	    fi \
          else \
	    echo "Cannot install library $(D0barD0installname), no installation directory specified"; \
	  fi; \
	fi

D0barD0clean :: D0barD0uninstall

uninstall :: D0barD0uninstall

D0barD0uninstall ::
	@if test ! "${installarea}" = ""; then \
	  cd $(bin); \
	  if test ! "$(install_dir)" = ""; then \
	    if test -d "$(install_dir)"; then \
	      echo "Removing installed library $(D0barD0installname) from $(install_dir)"; \
	      $(cmt_uninstall_area_command) $(install_dir)/$(D0barD0installname); \
	      $(cmt_uninstall_area_command) $(install_dir)/$(D0barD0installname).cmtref; \
	    fi \
          else \
	    echo "Cannot uninstall library $(D0barD0installname), no installation directory specified"; \
	  fi; \
	fi




#-- start of dependency ------------------
ifneq ($(MAKECMDGOALS),D0barD0clean)

#$(bin)D0barD0_dependencies.make :: dirs

ifndef QUICK
$(bin)D0barD0_dependencies.make : ../src/D0barD0.cxx $(use_requirements) $(cmt_final_setup_D0barD0)
	$(echo) "(D0barD0.make) Rebuilding $@"; \
	  $(build_dependencies) D0barD0 -all_sources -out=$@ ../src/D0barD0.cxx
endif

#$(D0barD0_dependencies)

-include $(bin)D0barD0_dependencies.make

endif
#-- end of dependency -------------------
#-- start of cpp_library -----------------

$(bin)D0barD0_dependencies.make : $(D0barD0_cxx_dependencies)

$(bin)$(binobj)D0barD0.o : $(D0barD0_cxx_dependencies)
	$(cpp_echo) $(src)D0barD0.cxx
	$(cpp_silent) $(cppcomp) -o $(@) $(use_pp_cppflags) $(D0barD0_pp_cppflags) $(lib_D0barD0_pp_cppflags) $(D0barD0_pp_cppflags) $(use_cppflags) $(D0barD0_cppflags) $(lib_D0barD0_cppflags) $(D0barD0_cppflags) $(D0barD0_cxx_cppflags)  $(src)D0barD0.cxx

#-- end of cpp_library ------------------
#-- start of cleanup_header --------------

clean :: D0barD0clean
	@cd .

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(D0barD0.make) $@: No rule for such target" >&2
#	@echo "#CMT> Warning: $@: No rule for such target" >&2; exit
else
.DEFAULT::
	$(echo) "(D0barD0.make) PEDANTIC: $@: No rule for such target" >&2
	if test $@ = "$(cmt_final_setup)" -o\
	 $@ = "$(cmt_final_setup_D0barD0)" ; then\
	 found=n; for s in 1 2 3 4 5; do\
	 sleep $$s; test ! -f $@ || { found=y; break; }\
	 done; if test $$found = n; then\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(D0barD0.make) PEDANTIC: $@: Seems to be missing. Ignore it for now" >&2; exit 0 ; fi;\
	 elif test `expr index $@ '/'` -ne 0 ; then\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(D0barD0.make) PEDANTIC: $@: Seems to be a missing file. Please check" >&2; exit 2 ; \
	 else\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(D0barD0.make) PEDANTIC: $@: Seems to be a fake target due to some pattern. Just ignore it" >&2 ; exit 0; fi
endif

D0barD0clean ::
#-- end of cleanup_header ---------------
#-- start of cleanup_library -------------
	$(cleanup_echo) library
	-$(cleanup_silent) cd $(bin); /bin/rm -f $(binobj)$(library_prefix)D0barD0$(library_suffix).a $(binobj)$(library_prefix)D0barD0$(library_suffix).s? $(binobj)D0barD0.stamp $(binobj)D0barD0.shstamp
#-- end of cleanup_library ---------------

