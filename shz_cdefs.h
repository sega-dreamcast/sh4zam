/*! \file
 *  \brief Preprocessor definitions and macro utilities.
 *
 *  This file contains commonly used preprocessor definitions used throughout
 *  the project:
 *      - Version information
 *      - Compiler attributes
 *      - Miscellaneous utilities
 *
 *  \author Falco Girgis
 */
#ifndef SHZ_CDEFS_H
#define SHZ_CDEFS_H

#include <stdint.h>

/*! \name   Versioning
 *  \brief  Current library version information.
 *  @{
 */
#define SHZ_VERSION_MAJOR       0   //!< Major release version number
#define SHZ_VERSION_MINOR       1   //!< Minor release version number
#define SHZ_VERSION_PATCH       0   //!< Patch release version number

//! Full release version number
#define SHZ_VERSION             ((uint32_t)((SHZ_VERSION_MAJOR << 24) | (SHZ_VERSION_MINOR << 8) | (SHZ_VERSION_PATCH)))
//! Full release version number string representation
#define SHZ_VERSION_STR         SHZ_STRINGIFY(SHZ_VERSION_MAJOR) "." SHZ_STRINGIFY(SHZ_VERSION_MINOR) "." SHZ_STRINGIFY(SHZ_VERSION_PATCH)
//! @}

/*! \name   Utilities
 *  \brief  Miscellaneous function-like macros
 *  @{
 */
 //! Stringifies an expression \i after preprocessing
#define SHZ_STRINGIFY(a)        SHZ_STRINGIFY_(a)
//! Returns the number of elements within a statically sized array
#define SHZ_COUNT_OF(array)    (sizeof(array) / sizeof((array)[0]))
//! Returns the containing structure from a pointer to one of its members
#define SHZ_CONTAINER_OF(ptr, type, member) \
    ((type*)((char*)(ptr) - offsetof(type, member)))

//! Swaps the contents of two variables
#define SHZ_SWAP(a, b) do { \
        auto tmp = a; \
        a = b; \
        b = tmp; \
    } while(false)
//! @}

//! \cond
/*! \name Compiler attributes
 *  \brief Defines for commonly-used GCC attributes.
 *  @{
 */
//! Forces a function or type to be aligned by \p N bytes.
#define SHZ_ALIGNAS(N)          __attribute__((aligned((N))))
//! Tells GCC that a scalar type is to be treated as a vector of size \p N.
#define SHZ_SIMD(N)             __attribute__((vector_size((N))))
//! Tells GCC that a particular function should be optimized for performance.
#define SHZ_HOT                 __attribute__((hot))
//! Aligns a function by the size of an icache line (32 bytes).
#define SHZ_ICACHE_ALIGNED      __attribute__((aligned(32)))
//! Forces GCC to inline the given function.
#define SHZ_FORCE_INLINE        __attribute__((always_inline)) SHZ_INLINE
//! Forces GCC to inline all calls to other functions made within the tagged function.
#define SHZ_FLATTEN             __attribute__((flatten))
//! Tells GCC not to introduce any extra padding for the given type.
#define SHZ_PACKED              __attribute__((packed))
//! Tells GCC the function has no effects other than returning a value that depends on its arguments and global variables.
#define SHZ_PURE                __attribute__((pure))

#ifndef __cplusplus
    //! Dummy define provided for C++ compatibility
#   define SHZ_DECLS_BEGIN
    //! Dummy define provided for C++ compatibility
#   define SHZ_DECLS_END
    //! Requests a function or member to be inlined (nonforcibly) OR to have static linkage.
#   define SHZ_INLINE           inline static
    //! Tells GCC the function has no effects other than returning a value that depends only on its arguments.
#   define SHZ_CONST            __attribute__((const))
#else
    //! Forces functions declared after this directive to use C linkage.
#   define SHZ_DECLS_BEGIN      extern "C" {
    //! Ends forcing functions to use C linkage.
#   define SHZ_DECLS_END        }
    //! Requests a function or member to be inlined (nonforcibly).
#   define SHZ_INLINE           inline
    //! Tells GCC the function has no effects other than returning a value that depends only on its arguments.
#   define SHZ_CONST            __attribute__((const)) constexpr
#endif
//! @}
//! \endcond

//! Namespace containing the C++23 interface of the SH4ZAM API.
namespace shz {
    //! Utility class template used give a derived class compatibility with a value type.
    template<typename P>
    class primitive_compatible {
    protected:
        P value_; //<! Encapsulated inner value of the requested type.
    public:
        //! Allows construction from an existing compatible value or its default value.
        SHZ_FORCE_INLINE primitive_compatible(P value={}) noexcept:
            value_(std::move(value)) {}
        //!Allows a derived class to convert to a value of the given type.
        SHZ_FORCE_INLINE operator P() const noexcept { return value_; }
        //! Allows a derived class to be assigned to an existing value of the given type.
        SHZ_FORCE_INLINE P operator=(P rhs) noexcept { value_ = std::move(rhs); }
    };
}

//! \cond
#define SHZ_STRINGIFY_(a)       #a
//! \endcond

#endif // SHZ_CDEFS_H
