/*
 *================================================================================
 * Copyright (c) 2019 Agi-Aero, All Rights Reserved
 *================================================================================
 * File description:
 * Athena mpi wrapper object
 *
 *================================================================================
 *    Date            Name                    Description of Change
 *    07-Apr-2019     Jiamin Xu               Creation
 *================================================================================
 */
#ifndef ATHENA_AthenaMPI_HPP
#define ATHENA_AthenaMPI_HPP

/* Athena headers */
#include "../Athena.hpp"

#ifdef ATHENA_HAVE_MPI
#include "mpi.h"
#else
/*!
 *  @brief Enumeration to define MPI constants when compiling without MPI.
 *
 *  These are defined in the global namespace because that's where MPI
 *  defines them. It does not matter what values these take because
 *  they are not used.  (They are just place holders to let code
 *  compile without MPI without requiring excessive preprocessor guards
 *  in the code.)
 *  This is not a complete set.  Developers should add as needed to extend
 *  AthenaMPI's functionality.
 */
enum
{
    MPI_COMM_WORLD,
    MPI_COMM_NULL,
    // Special values:
    MPI_SUCCESS = 0,
    MPI_CONGRUENT,
    MPI_IDENT,
    MPI_REQUEST_NULL,
    MPI_ERR_IN_STATUS,
    MPI_UNDEFINED,
    MPI_ANY_SOURCE,
    MPI_ANY_TAG,
    // Data types:
    MPI_BYTE,
    MPI_CHAR,
    MPI_DOUBLE,
    MPI_FLOAT,
    MPI_INT,
    MPI_LONG,
    MPI_C_DOUBLE_COMPLEX,
    MPI_2INT,
    MPI_DOUBLE_INT,
    MPI_FLOAT_INT,
    // Operations:
    MPI_MIN,
    MPI_MINLOC,
    MPI_MAX,
    MPI_MAXLOC,
    MPI_SUM,
    // Attributes:
    MPI_TAG_UB
};
#endif

/* c++ headers */
#include <sys/times.h>
#include <unistd.h>

/*
 *================================================================================
 *    Forward declarations
 *================================================================================
 */

/*
 *================================================================================
 *    Class namespaces
 *================================================================================
 */
namespace ATHENA
{
/*!
 *  @brief Provides C++ wrapper around MPI routines.
 *
 *  AthenaMPI provides a single point of access in ATHENA for using MPI
 *  function calls and for the run-time decision whether to use MPI.
 *  The purpose of having a single point is to facilitate writing code
 *  that is not cluttered by the repetitive logic absorbed into this class.
 *  Codes accessing MPI through this class should work whether ATHENA is
 *  configured with or without MPI and whether MPI is enabled at run time.
 *
 *  If ATHENA has MPI enabled, the MPI wrappers in this class delegate to
 *  the real MPI methods. Otherwise, they are no-ops and will throw an
 *  assertion if used, except for those specifically identified as able to
 *  work without MPI enabled.  The purpose of these interfaces are strictly
 *  to check whether MPI was configured into ATHENA and ATHENA is using
 *  MPI at run time.  They are not "single-process implementations" of the
 *  MPI standard.
 */
class AthenaMPI
{
public:
    /*!
     *  @brief Aliases for MPI data type names.
     *
     *  Define aliases for MPI types that can be used whether ATHENA is
     *  configured with or without MPI.  Without MPI, these types are "dummies",
     *  used to allow the code to be compiled without changes.
     */
#ifdef ATHENA_HAVE_MPI
    typedef MPI_Comm     Comm;
    typedef MPI_Datatype Datatype;
    typedef MPI_Group    Group;
    typedef MPI_Op       Op;
    typedef MPI_Request  Request;
    typedef MPI_Status   Status;
#else
    typedef int Comm;
    typedef int Datatype;
    typedef int Group;
    typedef int Op;
    typedef int Request;

    /*!
     *  @brief Dummy definition of Status to match the MPI standard.
     *
     *  Codes are allowed to access the members of this struct, so they must
     *  exist for compilation.  Without MPI, we won't actually use them.
     */
    struct Status
    {
        Status();
        int MPI_SOURCE;
        int MPI_TAG;
        int MPI_ERROR;
    };
#endif

    /*!
     *  @brief Get the primary AthenaMPI object owned by ATHENA.
     *
     *  This is ATHENA's primary communication object set up when
     *  AthenaMPI is initialized. It is used for basic communications
     *  that are not associated with another communication object.
     *  Various parts of the ATHENA library may create and use (and
     *  destroy) communicators that are derived from this object.
     *
     *  The use of this object outside of the ATHENA library should be
     *  carefully limited to avoid mixing messages.
     *
     *  After AthenaMPI::Init() and before AthenaMPI::Finalize(), the
     *  object returned is useable. Otherwise it is intentionally
     *  invalid.
     *
     *  @see Init()
     */
    static const AthenaMPI& GetAthenaWorld() { return d_athenaWorld; }

    /*!
     *  @brief Get a static invalid rank number.
     *
     *  This value is intended to be used by other classes as an invalid rank
     *  number rather than using a hard-coded "magic" negative integer value.
     */
    static int GetInvalidRank() { return d_invalidRank; }

    /*!
     *  @brief Constructor.
     *
     *  The given MPI communicator will be used for all communications invoked
     *  by this object.
     *
     *  Note that the object will NOT automatically free the communicator.
     *  To manually free the communicator, use freeCommunicator().
     *
     *  If the specified communicator is MPI_COMM_NULL, the rank (see getRank())
     *  and size (see getSize()) are set to invalid values.  Otherwise, the
     *  rank and size are set using the given communicator.  If MPI is enabled
     *  but MPI has not been initialized, the rank and size are set to invalid
     *  values. If MPI is not enabled, the rank is set to 0 and size to 1.
     */
    explicit AthenaMPI(const Comm& comm);

    /*!
     *  @brief Copy constructor.
     */
    AthenaMPI(const AthenaMPI& other);

    /*!
     *  @brief Get the local process rank from the last time the
     *  internal communicator was set.
     */
    int GetRank() const { return d_rank; }

    /*!
     *  @brief Get the size (number of processes) of the internal
     *  communicator the last time it was set.
     */
    int GetSize() const { return d_size; }

    bool IsMasterRank() const {return d_rank == MASTER_NODE;}

    /*!
     *  @brief Get the internal communicator.
     */
    const Comm& GetCommunicator() const { return d_comm; }

    /*!
     *  @brief Set the internal communicator.
     *
     *  Note that this call does does automatically free the
     *  existing communicator.  To manually free communicators, see
     *  freeCommunicator().
     *
     *  @param[in] comm
     */
    void SetCommunicator(const Comm& comm);

    /*!
     *  @brief Duplicate and internally use the communicator of a given
     *  AthenaMPI object.
     *
     *  Note that this call does not automatically free the
     *  existing communicator. The duplicate communicator will also NOT
     *  be automatically freed. To manually free communicators, see
     *  FreeCommunicator().
     *
     *  If ATHENA isn't configured with MPI, the duplicate is an
     *  identical copy.
     */
    void DupCommunicator(const AthenaMPI& other);

    /*!
     *  @brief Free the internal communicator and set it to MPI_COMM_NULL.
     *
     *  If the internal communicator is already MPI_COMM_NULL, do nothing.
     */
    void FreeCommunicator();

    /*!
     *  @brief Compare with another AthenaMPI's communicator.
     *
     *  If MPI is enabled, compare using Comm_compare, and return the result.
     *  Otherwise, return MPI_IDENT if the two communicators are the same
     *  and MPI_CONGRUENT if they are not.  (No other choice makes sense
     *  when MPI is disabled.)
     *
     *  Performance of this method depends on underlying MPI implementation
     *  and may not scale.
     */
    int CompareCommunicator(const AthenaMPI& other) const;

    /*!
     *  @brief Whether the communicator is MPI_COMM_NULL.
     */
    bool HasNullCommunicator() const { return d_comm == MPI_COMM_NULL; }

    /*!
     *  @brief Whether the communicator is congruent with another's.
     *
     *  Performance of this method depends on underlying MPI implementation
     *  and may not scale.
     */
    bool IsCongruentWith(const AthenaMPI& other) const
    {
#ifdef ATHENA_HAVE_MPI
        int compareResult = CompareCommunicator(other);
        return compareRresult == MPI_CONGRUENT || compareResult == MPI_IDENT;

#else
        return d_comm != MPI_COMM_NULL && d_comm == other.d_comm;

#endif
    }

    /*!
     *  @brief Assignment operator.
     */
    AthenaMPI& operator=(const AthenaMPI& rhs)
    {
        d_comm = rhs.d_comm;
        d_rank = rhs.d_rank;
        d_size = rhs.d_size;
        return *this;
    }

    /*!
     *  @brief Equality comparison operator (compares MPI communicator).
     */
    bool operator==(const AthenaMPI& rhs) const { return d_comm == rhs.d_comm; }

    /*!
     *  @brief Inequality comparison operator (compares MPI communicator).
     */
    bool operator!=(const AthenaMPI& rhs) const { return d_comm != rhs.d_comm; }

    //@{
    //!  @name Static MPI wrappers matching MPI interfaces.
    static int Comm_rank(Comm comm, int* rank);
    static int Comm_size(Comm comm, int* size);
    static int Comm_compare(Comm comm1, Comm comm2, int* result);
    static int Comm_free(Comm* comm);
    static int Finalized(int* flag);
    static int Get_count(Status* status, Datatype datatype, int* count);
    static int Request_free(Request* request);
    static int Test(Request* request, int* flag, Status* status);
    static int Test_cancelled(Status* status, int* flag);
    static int Wait(Request* request, Status* status);
    static int Waitall(int count, Request* reqs, Status* stats);
    static int Waitany(int count, Request* array_of_requests, int* index, Status* status);
    static int
                  Waitsome(int incount, Request* array_of_requests, int* outcount, int* array_of_indices, Status* array_of_statuses);
    static double Wtime();
    //@}

    //@{
    //!  @name MPI wrappers for methods associated with an MPI communicator.
    int
         Allgather(void* sendbuf, int sendcount, Datatype sendtype, void* recvbuf, int recvcount, Datatype recvtype) const;
    int  Allgatherv(void*    sendbuf,
                    int      sendcvount,
                    Datatype sendtype,
                    void*    recvbuf,
                    int*     recvcounts,
                    int*     displs,
                    Datatype recvtype) const;
    int  Allreduce(void* sendbuf, void* recvbuf, int count, Datatype datatype, Op op) const;
    int  Attr_get(int keyval, void* attribute_val, int* flag) const;
    int  Barrier() const;
    int  Bcast(void* buffer, int count, Datatype datatype, int root) const;
    int  Comm_dup(Comm* newcomm) const;
    int  Comm_rank(int* rank) const;  // MPI Comm_rank (Set rank to 0 when MPI is disabled).
    int  Comm_size(int* size) const;  // MPI Comm_size (Set size to 1 when MPI is disabled).
    int  Gather(void*    sendbuf,
                int      sendcount,
                Datatype sendtype,
                void*    recvbuf,
                int      recvcount,
                Datatype recvtype,
                int      root) const;
    int  Gatherv(void*    sendbuf,
                 int      sendcount,
                 Datatype sendtype,
                 void*    recvbuf,
                 int*     recvcounts,
                 int*     displs,
                 Datatype recvtype,
                 int      root) const;
    int  Iprobe(int source, int tag, int* flag, Status* status) const;
    int  Isend(void* buf, int count, Datatype datatype, int dest, int tag, Request* req) const;
    int  Irecv(void* buf, int count, Datatype datatype, int source, int tag, Request* request) const;
    int  Probe(int source, int tag, Status* status) const;
    int  Recv(void* buf, int count, Datatype datatype, int source, int tag, Status* status) const;
    int  Reduce(void* sendbuf, void* recvbuf, int count, Datatype datatype, Op op, int root) const;
    int  Send(void* buf, int count, Datatype datatype, int dest, int tag) const;
    int  Sendrecv(void*    sendbuf,
                  int      sendcount,
                  Datatype sendtype,
                  int      dest,
                  int      sendtag,
                  void*    recvbuf,
                  int      recvcount,
                  Datatype recvtype,
                  int      source,
                  int      recvtag,
                  Status*  status) const;
    int  Scan(void* sendbuf, void* recvbuf, int count, Datatype datatype, Op op) const;
    int  AllReduce(int* x, int count, Op op, int* ranks_of_extrema = 0) const;
    int  AllReduce(double* x, int count, Op op, int* ranks_of_extrema = 0) const;
    int  AllReduce(float* x, int count, Op op, int* ranks_of_extrema = 0) const;
    int  ParallelPrefixSum(int* x, int count, int tag) const;
    bool HasReceivableMessage(Status* status = 0, int source = MPI_ANY_SOURCE, int tag = MPI_ANY_TAG) const;
    //@}

    /*!
     *  @brief Set flag indicating whether exit or MPI_Abort is called
     *  when running with one processor.
     *
     *  Calling this function influences the behavior of calls to
     *  AthenaMPI::Abort(). If the value set is true, it means that
     *  system abort() will be called. Passing false means exit(-1) will be
     *  called.
     */
    static void SetCallAbortInSerialInsteadOfExit(bool flag = true) { d_callAbortInSerialInsteadOfExit = flag; }

    /*!
     *  @brief Set flag indicating whether MPI_Abort or abort is called
     *  when running with more than one processor.
     *
     *  Calling this function influences the behavior of calls to
     *  AthenaMPI::Abort().  If the value set is true, it means that
     *  system abort() will be called. Passing false means MPI_Abort will be
     *  called.
     */
    static void SetCallAbortInParallelInsteadOfMPIAbort(bool flag = true)
    {
        d_callAbortInParallelInsteadOfMpiAbort = flag;
    }

    /*!
     *  @brief Call MPI_Abort or exit depending on whether running with one
     *  or more processes and value set by function above, if called.
     *
     *  The default is to call exit(-1) if running with one processor and to
     *  call MPI_Abort() otherwise.  This function avoids having to guard abort
     *  calls in application code.
     */
    static void Abort();

    /*!
     *  @brief Disable MPI usage and run in sequential mode.
     *
     *  The default setting is to enable MPI at run-time if ATHENA was
     *  configured with MPI and to disable if ATHENA was not configured
     *  with MPI.  This method disables MPI in the former case.
     *
     *  If MPI is disabled for ATHENA, the communication interfaces in
     *  this class are no-ops and will throw an assertion if used,
     *  except for those interfaces specifically described as working in
     *  sequential mode.
     *
     *  Disabling MPI must be done before calling AthenaMPI::init().
     */
    static void DisableMPI();

    /*!
     *  @brief Whether ATHENA is using MPI (configured, compiled and
     *  initialized).
     *
     *  @see disableMPI().
     */
    static bool UsingMPI() { return d_mpiIsInitialized; }

    /*!
     *  @brief Initialize MPI and AthenaMPI.
     *
     *  This initialization sets up getATHENAWorld() to return an
     *  AthenaMPI object with a communicator duplicated from
     *  MPI_COMM_WORLD.
     *
     *  Use only one of the three initialization methods.
     *
     *  @param[in]  argc  Pointer to parameter from main()
     *  @param[in]  argv  Pointer to parameter from main()
     */
    static void Init(int* argc, char** argv[]);

    /*!
     *  @brief Initialize AthenaMPI when MPI is already initialized.
     *
     *  This initialization sets up getATHENAWorld() to return an
     *  AthenaMPI object with a communicator duplicated from
     *  the one passed in.
     *
     *  Use only one of the three initialization methods.
     *
     *  @param comm  An MPI Communicator to be duplicated for ATHENA use.
     */
    static void Init(Comm comm);

    /*!
     *  @brief Initialize AthenaMPI to work without MPI.
     *
     *  This initialization sets up ATHENA to run in sequential mode.
     *  Use only one of the three initialization methods.
     */
    static void InitMPIDisabled();

    /*!
     *  @brief Shut down AthenaMPI and, if appropriate, shut down MPI.
     *
     *  This method frees the MPI communicator duplicated for ATHENA
     *  use. If this class has started MPI with the first Init() method,
     *  Finalize() will also shut down MPI.
     */
    static void Finalize();

private:
    struct DoubleIntStruct
    {
        double d;
        int    i;
    }; /**< @brief Structs for passing arguments to MPI. */
    struct FloatIntStruct
    {
        float f;
        int   i;
    }; /**< @brief Structs for passing arguments to MPI. */
    struct IntIntStruct
    {
        int j;
        int i;
    }; /**< @brief Structs for passing arguments to MPI. */

    AthenaMPI(); /**< @brief Unimplemented default constructor. */

    AthenaMPI::Comm d_comm; /**< @brief Internal communicator. */
    int             d_rank; /**< @brief The local rank. */
    int             d_size; /**< @brief The size of the communicator. */

    static int  d_invalidRank;      /**< @brief Invalid (negative) rank number for getInvalidRank(). */
    static bool d_mpiIsInitialized; /**< @brief Whether the actual MPI library (not this wrapper) is initialized. */
    static bool d_weStartedMpi;     /**< @brief Whether this class started up MPI. */
    static AthenaMPI d_athenaWorld; /**< @brief Primary AthenaMPI object. */
    static bool d_callAbortInSerialInsteadOfExit; /**< @brief Flags to control program abort in AthenaMPI::abort(). */
    static bool
        d_callAbortInParallelInsteadOfMpiAbort; /**< @brief Flags to control program abort in AthenaMPI::abort(). */

};  // end class AthenaMPI
}  // end namespace ATHENA

#endif
