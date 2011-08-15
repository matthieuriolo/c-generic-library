ACLOCAL_AMFLAGS=-I m4
EXTRA_DIST = reconf


#used to install the headers with the subfolder (without nobase_ the folder won't be copied one be one - including the subfolders)
#automake does not remove the ../ out of the path, so the files are copied to /usr/local/include/../libcgeneric -> /usr/local/libcgeneric
#the problem above is the reason why we have to put it here (and not inside lib/ or include)
incDIR=./libcgeneric
srcHEADERS=$(incDIR)/libcgeneric.h $(incDIR)/binary_tree.h $(incDIR)/deque.h $(incDIR)/heap.h $(incDIR)/node.h $(incDIR)/queue.h $(incDIR)/vector.h $(incDIR)/comparisons.h $(incDIR)/hashtable.h $(incDIR)/list.h $(incDIR)/priority_queue.h $(incDIR)/stack.h $(incDIR)/gen/access_macros.h $(incDIR)/gen/control_macros.h $(incDIR)/gen/error_macros.h $(incDIR)/gen/function_signatures.h $(incDIR)/gen/stdint.h $(incDIR)/gen/control_arr_macros.h $(incDIR)/gen/data_types.h $(incDIR)/gen/function_macros.h $(incDIR)/gen/gen_macros.h
libincludedir=$(includedir)
nobase_libinclude_HEADERS=$(srcHEADERS)

manDIR=./doc/man/man3/
man_MANS=$(manDIR)BinaryTree.3 $(manDIR)/_array_iter.3 $(manDIR)/_prio_queue.3 $(manDIR)/data_types.h.3 $(manDIR)/list.h.3 $(manDIR)/DequeList.3 $(manDIR)/_array_struct.3 $(manDIR)/_prio_queue_node.3 $(manDIR)/deque.h.3 $(manDIR)/node.h.3 $(manDIR)/List.3 $(manDIR)/_bfs_iter.3 $(manDIR)/_ptr_iter.3 $(manDIR)/error_macros.h.3 $(manDIR)/priority_queue.h.3 $(manDIR)/ListIter.3 $(manDIR)/_closed_hash_iterator.3 $(manDIR)/_ptr_struct.3 $(manDIR)/function_macros.h.3 $(manDIR)/queue.h.3 $(manDIR)/QueueList.3 $(manDIR)/_closed_hash_table.3 $(manDIR)/access_macros.h.3 $(manDIR)/function_signatures.h.3 $(manDIR)/stack.h.3 $(manDIR)/StackList.3 $(manDIR)/_dfs_iter.3 $(manDIR)/binary_tree.h.3 $(manDIR)/gen_macros.h.3 $(manDIR)/stdint.h.3 $(manDIR)/_Hash_List_Node.3 $(manDIR)/_functor_api.3 $(manDIR)/comparisons.h.3 $(manDIR)/hashtable.h.3 $(manDIR)/vector.h.3 $(manDIR)/_Hash_Node.3 $(manDIR)/_open_hash_iterator.3 $(manDIR)/control_arr_macros.h.3 $(manDIR)/heap.h.3 $(manDIR)/_Node.3 $(manDIR)/_open_hash_table.3 $(manDIR)/control_macros.h.3 $(manDIR)/libcgeneric.h.3


SUBDIRS = m4 doc src lib

if enable_tests
SUBDIRS += tests
endif

if enable_units
SUBDIRS += units
endif

INCLUDES = -I$(top_srcdir)/src
LDFLAGS = -L$(top_srcdir)/lib
LDADD = -lcgeneric
