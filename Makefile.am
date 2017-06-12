## libsmpppdu:
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
lib_LTLIBRARIES = libsmpppdu-@SMPP_PDU_API_VERSION@.la

## Define the source file list for the "libexample-@EXAMPLE_API_VERSION@.la"
## target.  Note that @EXAMPLE_API_VERSION@ is not interpreted by Automake and
## will therefore be treated as if it were literally part of the target name,
## and the variable name derived from that.
## The file extension .cc is recognized by Automake, and makes it produce
## rules which invoke the C++ compiler to produce a libtool object file (.lo)
## from each source file.  Note that it is not necessary to list header files
## which are already listed elsewhere in a _HEADERS variable assignment.
libsmpppdu_@SMPP_PDU_API_VERSION@_la_SOURCES = smpppdu/alert_notification.cpp       \
                                                smpppdu/bind_receiver.cpp            \
                                                smpppdu/bind_receiver_resp.cpp       \
                                                smpppdu/bind_transceiver.cpp         \
                                                smpppdu/bind_transceiver_resp.cpp    \
                                                smpppdu/bind_transmitter.cpp         \
                                                smpppdu/bind_transmitter_resp.cpp    \
                                                smpppdu/bind_type.cpp                \
                                                smpppdu/bind_type_resp.cpp           \
                                                smpppdu/broadcast_sm.cpp             \
                                                smpppdu/broadcast_sm_resp.cpp        \
                                                smpppdu/cancel_broadcast_sm.cpp      \
                                                smpppdu/cancel_broadcast_sm_resp.cpp \
                                                smpppdu/cancel_sm.cpp                \
                                                smpppdu/cancel_sm_resp.cpp           \
                                                smpppdu/data_sm.cpp                  \
                                                smpppdu/data_sm_resp.cpp             \
                                                smpppdu/deliver_sm.cpp               \
                                                smpppdu/deliver_sm_resp.cpp          \
                                                smpppdu/enquire_link.cpp             \
                                                smpppdu/enquire_link_resp.cpp        \
                                                smpppdu/error.cpp                    \
                                                smpppdu/generic_nack.cpp             \
                                                smpppdu/header_pdu.cpp               \
                                                smpppdu/octet_array.cpp              \
                                                smpppdu/outbind.cpp                  \
                                                smpppdu/query_broadcast_sm.cpp       \
                                                smpppdu/query_broadcast_sm_resp.cpp  \
                                                smpppdu/query_sm.cpp                 \
                                                smpppdu/query_sm_resp.cpp            \
                                                smpppdu/replace_sm.cpp               \
                                                smpppdu/replace_sm_resp.cpp          \
                                                smpppdu/sequence_number.cpp          \
                                                smpppdu/smpppdu.cpp                 \
                                                smpppdu/standard_parameters.cpp      \
                                                smpppdu/submit_multi.cpp             \
                                                smpppdu/submit_multi_resp.cpp        \
                                                smpppdu/submit_sm.cpp                \
                                                smpppdu/submit_sm_resp.cpp           \
                                                smpppdu/tlv.cpp                      \
                                                smpppdu/tlv_list.cpp                 \
                                                smpppdu/unbind.cpp                   \
                                                smpppdu/unbind_resp.cpp

## Instruct libtool to include ABI version information in the generated shared
## library file (.so).  The library ABI version is defined in configure.ac, so
## that all version information is kept in one place.
libsmpppdu_@SMPP_PDU_API_VERSION@_la_LDFLAGS = -version-info 1

## Define the list of public header files and their install location.  The
## nobase_ prefix instructs Automake to not strip the directory part from each
## filename, in order to avoid the need to define separate file lists for each
## installation directory.  This only works if the directory hierarchy in the
## source tree matches the hierarchy at the install location, however.
smpppdu_includedir = $(includedir)/smpppdu-$(SMPP_PDU_API_VERSION)
nobase_smpppdu_include_HEADERS = smpppdu_all.hpp                 \
                                 smpppdu/alert_notification.hpp       \
                                 smpppdu/bind_receiver.hpp            \
                                 smpppdu/bind_receiver_resp.hpp       \
                                 smpppdu/bind_transceiver.hpp         \
                                 smpppdu/bind_transceiver_resp.hpp    \
                                 smpppdu/bind_transmitter.hpp         \
                                 smpppdu/bind_transmitter_resp.hpp    \
                                 smpppdu/bind_type.hpp                \
                                 smpppdu/bind_type_resp.hpp           \
                                 smpppdu/broadcast_sm.hpp             \
                                 smpppdu/broadcast_sm_resp.hpp        \
                                 smpppdu/cancel_broadcast_sm.hpp      \
                                 smpppdu/cancel_broadcast_sm_resp.hpp \
                                 smpppdu/cancel_sm.hpp                \
                                 smpppdu/cancel_sm_resp.hpp           \
                                 smpppdu/command_id.hpp               \
                                 smpppdu/command_length.hpp           \
                                 smpppdu/command_status.hpp           \
                                 smpppdu/data_sm.hpp                  \
                                 smpppdu/data_sm_resp.hpp             \
                                 smpppdu/deliver_sm.hpp               \
                                 smpppdu/deliver_sm_resp.hpp          \
                                 smpppdu/endian_util.hpp              \
                                 smpppdu/enquire_link.hpp             \
                                 smpppdu/enquire_link_resp.hpp        \
                                 smpppdu/error.hpp                    \
                                 smpppdu/generic_nack.hpp             \
                                 smpppdu/header_pdu.hpp               \
                                 smpppdu/lexical_cast.hpp             \
                                 smpppdu/octet_array.hpp              \
                                 smpppdu/octet.hpp                    \
                                 smpppdu/outbind.hpp                  \
                                 smpppdu/query_broadcast_sm.hpp       \
                                 smpppdu/query_broadcast_sm_resp.hpp  \
                                 smpppdu/query_sm.hpp                 \
                                 smpppdu/query_sm_resp.hpp            \
                                 smpppdu/replace_sm.hpp               \
                                 smpppdu/replace_sm_resp.hpp          \
                                 smpppdu/sequence_number.hpp          \
                                 smpppdu/smpppdu.hpp                 \
                                 smpppdu/standard_parameters.hpp      \
                                 smpppdu/submit_multi.hpp             \
                                 smpppdu/submit_multi_resp.hpp        \
                                 smpppdu/submit_sm.hpp                \
                                 smpppdu/submit_sm_resp.hpp           \
                                 smpppdu/tlv.hpp                      \
                                 smpppdu/tlv_list.hpp                 \
                                 smpppdu/unbind.hpp                   \
                                 smpppdu/unbind_resp.hpp

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
smpppdu_libincludedir = $(libdir)/smpppdu-$(SMPP_PDU_API_VERSION)/include
nodist_smpppdu_libinclude_HEADERS = smpppduconfig.h

## Install the generated pkg-config file (.pc) into the expected location for
## architecture-dependent package configuration information.  Occasionally,
## pkg-config files are also used for architecture-independent data packages,
## in which case the correct install location would be $(datadir)/pkgconfig.
pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = smpppdu-$(SMPP_PDU_API_VERSION).pc

## Define an independent executable script for inclusion in the distribution
## archive.  However, it will not be installed on an end user's system due to
## the noinst_ prefix.
dist_noinst_SCRIPTS = autogen.sh
