// Copyright (c) 2016 Deepin Ltd. All rights reserved.
// Use of this source is governed by General Public License that can be found
// in the LICENSE file.

#ifndef INSTALLER_PARTMAN_PARTITION_H
#define INSTALLER_PARTMAN_PARTITION_H

#include <QList>
#include <QStringList>

#include "partman/fs.h"
#include "partman/structs.h"

namespace installer {

enum class PartitionType {
  Primary,
  Logical,
  Extended,
  Unallocated,
};

enum class PartitionStatus {
  Real,
  New,
  Formatted,
};

class Partition {
 public:
  Partition();
  ~Partition();

  bool operator==(const Partition& other) const;

  QString device_path;
  QString path;
  QString uuid;
  QString label;
  QString part_label;  // Only some partition tables support part-label.
  int partition_number;
  PartitionType type;
  PartitionStatus status;
  FsType fs;
  OsType os;

  // sector size of the disk device needed for converting to/from sectors
  // and bytes
  qint64 sector_size;

  qint64 length;
  qint64 freespace;

  qint64 sector_start;
  qint64 sector_end;

  // No. of sectors not unallocated before/after this partition.
  // These two properties are only used while creating a new partition.
  // If it is a valid value, create an unallocated-partition later.
  qint64 sectors_unallocated_preceding;
  qint64 sectors_unallocated_succeeding;

  QString mount_point;

  // Returns actual partition size.
  // |length| is set only if this partition has a filesystem.
  qint64 getByteLength() const;

  // Returns a sector within this partition.
  // This method is only useful when calling ped_disk_get_partition_by_sector()
  qint64 getSector() const;

  // Returns length in sector.
  qint64 getSectorLength() const;
};

typedef QList<Partition> PartitionList;

// Get index of extended partition in |partitions|. Returns -1 if not found.
int ExtendedPartitionIndex(const PartitionList& partitions);

// Get index of |partition| in |partitions|. Returns -1 if not found.
int PartitionIndex(const PartitionList& partitions, const Partition& partition);

// Get number of primary partitions, together with extended partition(if found).
int SumOfPrimarys(const PartitionList& partitions);

}  // namespace installer

#endif  // INSTALLER_PARTMAN_PARTITION_H