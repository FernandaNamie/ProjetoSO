/* 32-bit compatibility syscall for 64-bit systems for DH operations
 *
 * Copyright (C) 2016 Stephan Mueller <smueller@chronox.de>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */

#include <linux/uaccess.h>

#include "internal.h"

/*
 * Perform the DH computation or DH based key derivation.
 *
 * If successful, 0 will be returned.
 */
long compat_keyctl_dh_compute(struct keyctl_dh_params __user *params,
			      char __user *buffer, size_t buflen,
			      struct compat_keyctl_kdf_params __user *kdf)
{
	struct keyctl_kdf_params kdfcopy;
	struct compat_keyctl_kdf_params compat_kdfcopy;

	if (!kdf)
		return __keyctl_dh_compute(params, buffer, buflen, NULL);

	if (copy_from_user(&compat_kdfcopy, kdf, sizeof(compat_kdfcopy)) != 0)
		return -EFAULT;

	kdfcopy.hashname = compat_ptr(compat_kdfcopy.hashname);
	kdfcopy.otherinfo = compat_ptr(compat_kdfcopy.otherinfo);
	kdfcopy.otherinfolen = compat_kdfcopy.otherinfolen;

	return __keyctl_dh_compute(params, buffer, buflen, &kdfcopy);
}
