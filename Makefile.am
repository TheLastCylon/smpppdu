## libsmpp_pdu:
## put descriptive splurge here.

## Place generated object files (.o) into the same directory as their source
## files, in order to avoid collisions when non-recursive make is used.
AUTOMAKE_OPTIONS = subdir-objects

## Additional flags to pass to aclocal when it is invoked automatically at
## make time. The ${ACLOCAL_FLAGS} variable is picked up from the environment
## to provide a way for the user to supply additional arguments.
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}

## Define a libtool archive target "libexample-@EXAMPLE_API_VERSION@.la", with
## @EXAMPLE_API_VERSION@ substituted into the generated Makefile at configure
## time.
## The libtool archive file (.la) will be installed into the directory named
## by the predefined variable $(bindir), along with the actual shared library
## file (.so).
lib_LTLIBRARIES = libsmpp_pdu-@SMPP_PDU_API_VERSION@.la

## Define the source file list for the "libexample-@EXAMPLE_API_VERSION@.la"
## target.  Note that @EXAMPLE_API_VERSION@ is not interpreted by Automake and
## will therefore be treated as if it were literally part of the target name,
## and the variable name derived from that.
## The file extension .cc is recognized by Automake, and makes it produce
## rules which invoke the C++ compiler to produce a libtool object file (.lo)
## from each source file.  Note that it is not necessary to list header files
## which are already listed elsewhere in a _HEADERS variable assignment.
libsmpp_pdu_@SMPP_PDU_API_VERSION@_la_SOURCES = smpp_pdu/alert_notification.cpp       \
                                                smpp_pdu/bind_receiver.cpp            \
                                                smpp_pdu/bind_receiver_resp.cpp       \
                                                smpp_pdu/bind_transceiver.cpp         \
                                                smpp_pdu/bind_transceiver_resp.cpp    \
                                                smpp_pdu/bind_transmitter.cpp         \
                                                smpp_pdu/bind_transmitter_resp.cpp    \
                                                smpp_pdu/bind_type.cpp                \
                                                smpp_pdu/bind_type_resp.cpp           \
                                                smpp_pdu/broadcast_sm.cpp             \
                                                smpp_pdu/broadcast_sm_resp.cpp        \
                                                smpp_pdu/cancel_broadcast_sm.cpp      \
                                                smpp_pdu/cancel_broadcast_sm_resp.cpp \
                                                smpp_pdu/cancel_sm.cpp                \
                                                smpp_pdu/cancel_sm_resp.cpp           \
                                                smpp_pdu/data_sm.cpp                  \
                                                smpp_pdu/data_sm_resp.cpp             \
                                                smpp_pdu/deliver_sm.cpp               \
                                                smpp_pdu/deliver_sm_resp.cpp          \
                                                smpp_pdu/enquire_link.cpp             \
                                                smpp_pdu/enquire_link_resp.cpp        \
                                                smpp_pdu/error.cpp                    \
                                                smpp_pdu/generic_nack.cpp             \
                                                smpp_pdu/header_pdu.cpp               \
                                                smpp_pdu/octet_array.cpp              \
                                                smpp_pdu/outbind.cpp                  \
                                                smpp_pdu/query_broadcast_sm.cpp       \
                                                smpp_pdu/query_broadcast_sm_resp.cpp  \
                                                smpp_pdu/query_sm.cpp                 \
                                                smpp_pdu/query_sm_resp.cpp            \
                                                smpp_pdu/replace_sm.cpp               \
                                                smpp_pdu/replace_sm_resp.cpp          \
                                                smpp_pdu/sequence_number.cpp          \
                                                smpp_pdu/smpp_pdu.cpp                 \
                                                smpp_pdu/standard_parameters.cpp      \
                                                smpp_pdu/submit_multi.cpp             \
                                                smpp_pdu/submit_multi_resp.cpp        \
                                                smpp_pdu/submit_sm.cpp                \
                                                smpp_pdu/submit_sm_resp.cpp           \
                                                smpp_pdu/tlv.cpp                      \
                                                smpp_pdu/tlv_list.cpp                 \
                                                smpp_pdu/unbind.cpp                   \
                                                smpp_pdu/unbind_resp.cpp

## Instruct libtool to include ABI version information in the generated shared
## library file (.so).  The library ABI version is defined in configure.ac, so
## that all version information is kept in one place.
libsmpp_pdu_@SMPP_PDU_API_VERSION@_la_LDFLAGS = -version-info 1

## Define the list of public header files and their install location.  The
## nobase_ prefix instructs Automake to not strip the directory part from each
## filename, in order to avoid the need to define separate file lists for each
## installation directory.  This only works if the directory hierarchy in the
## source tree matches the hierarchy at the install location, however.
smpp_pdu_includedir = $(includedir)/smpp_pdu-$(SMPP_PDU_API_VERSION)
nobase_smpp_pdu_include_HEADERS = smpp_pdu_all.hpp                 \
                                  smpp_pdu/alert_notification.hpp       \
                                  smpp_pdu/bind_receiver.hpp            \
                                  smpp_pdu/bind_receiver_resp.hpp       \
                                  smpp_pdu/bind_transceiver.hpp         \
                                  smpp_pdu/bind_transceiver_resp.hpp    \
                                  smpp_pdu/bind_transmitter.hpp         \
                                  smpp_pdu/bind_transmitter_resp.hpp    \
                                  smpp_pdu/bind_type.hpp                \
                                  smpp_pdu/bind_type_resp.hpp           \
                                  smpp_pdu/broadcast_sm.hpp             \
                                  smpp_pdu/broadcast_sm_resp.hpp        \
                                  smpp_pdu/cancel_broadcast_sm.hpp      \
                                  smpp_pdu/cancel_broadcast_sm_resp.hpp \
                                  smpp_pdu/cancel_sm.hpp                \
                                  smpp_pdu/cancel_sm_resp.hpp           \
                                  smpp_pdu/command_id.hpp               \
                                  smpp_pdu/command_length.hpp           \
                                  smpp_pdu/command_status.hpp           \
                                  smpp_pdu/data_sm.hpp                  \
                                  smpp_pdu/data_sm_resp.hpp             \
                                  smpp_pdu/deliver_sm.hpp               \
                                  smpp_pdu/deliver_sm_resp.hpp          \
                                  smpp_pdu/endian_util.hpp              \
                                  smpp_pdu/enquire_link.hpp             \
                                  smpp_pdu/enquire_link_resp.hpp        \
                                  smpp_pdu/error.hpp                    \
                                  smpp_pdu/generic_nack.hpp             \
                                  smpp_pdu/header_pdu.hpp               \
                                  smpp_pdu/lexical_cast.hpp             \
                                  smpp_pdu/octet_array.hpp              \
                                  smpp_pdu/octet.hpp                    \
                                  smpp_pdu/outbind.hpp                  \
                                  smpp_pdu/query_broadcast_sm.hpp       \
                                  smpp_pdu/query_broadcast_sm_resp.hpp  \
                                  smpp_pdu/query_sm.hpp                 \
                                  smpp_pdu/query_sm_resp.hpp            \
                                  smpp_pdu/replace_sm.hpp               \
                                  smpp_pdu/replace_sm_resp.hpp          \
                                  smpp_pdu/sequence_number.hpp          \
                                  smpp_pdu/smpp_pdu.hpp                 \
                                  smpp_pdu/standard_parameters.hpp      \
                                  smpp_pdu/submit_multi.hpp             \
                                  smpp_pdu/submit_multi_resp.hpp        \
                                  smpp_pdu/submit_sm.hpp                \
                                  smpp_pdu/submit_sm_resp.hpp           \
                                  smpp_pdu/tlv.hpp                      \
                                  smpp_pdu/tlv_list.hpp                 \
                                  smpp_pdu/unbind.hpp                   \
                                  smpp_pdu/unbind_resp.hpp

## The generated configuration header is installed in its own subdirectory of
## $(libdir).  The reason for this is that the configuration information put
## into this header file describes the target platform the installed library
## has been built for.  Thus the file must not be installed into a location
## intended for architecture-independent files, as defined by the Filesystem
## Hierarchy Standard (FHS).
## The nodist_ prefix instructs Automake to not generate rules for including
## the listed files in the distribution on 'make dist'.  Files that are listed
## in _HEADERS variables are normally included in the distribution, but the
## configuration header file is generated at configure time and should not be
## shipped with the source tarball.
smpp_pdu_libincludedir = $(libdir)/smpp_pdu-$(SMPP_PDU_API_VERSION)/include
nodist_smpp_pdu_libinclude_HEADERS = smpp_pduconfig.h

## Install the generated pkg-config file (.pc) into the expected location for
## architecture-dependent package configuration information.  Occasionally,
## pkg-config files are also used for architecture-independent data packages,
## in which case the correct install location would be $(datadir)/pkgconfig.
pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = smpp_pdu-$(SMPP_PDU_API_VERSION).pc

## Define an independent executable script for inclusion in the distribution
## archive.  However, it will not be installed on an end user's system due to
## the noinst_ prefix.
dist_noinst_SCRIPTS = autogen.sh
