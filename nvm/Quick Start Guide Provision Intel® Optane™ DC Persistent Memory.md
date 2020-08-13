## Introduction

[Intel® Optane™ DC persistent memory](https://www.intel.com/content/www/us/en/architecture-and-technology/optane-dc-persistent-memory.html) 

英特尔®傲腾™DC持久性内存是一种破坏性技术，可在内存和存储之间建立新的层次。英特尔®OptaneTM DC内存模块支持两种模式-易失性用例的内存模式和App Direct模式，后者提供可字节寻址的持久存储。有关每种操作模式的更多信息，请参阅《英特尔Optane DC持久性存储器操作模式介绍》一文。

在本指南中，我们提供了有关使用ipmctl实用程序和其他基本方法，使用特定于操作系统的名称空间管理工具向应用程序公开持久性内存名称空间的配置和管理Intel Optane DC内存模块的说明。

ipmctl是由Intel创建并维护的开源实用程序，专门用于配置和管理Intel Optane DC内存模块。可以从GitHub *上的ipmctl项目页面上将它用于Linux *和Windows *。

Linux和Windows中都有与供应商无关的工具，可用于管理非易失性双列直插式内存模块（NVDIMM）。非易失性设备控制（ndctl）是一种用于在Linux中管理名称空间的开源实用程序，Microsoft *已创建PowerShell * cmdlet来进行持久性内存名称空间管理。

## Persistent Memory Provisioning Concepts

本节介绍适用于NVDIMM的配置和管理的基本术语和概念。

### Region

一个region是一组一个或多个NVDIMM，也称为交错集。可以按n路交错或非交错方式创建区域。交错是一种使多个永久性存储设备显示为单个逻辑虚拟地址空间的技术。它允许将页面内的相邻虚拟地址分布在多个存储设备上。这种硬件级别的并行性增加了设备的可用带宽。只能使用ipmctl在Intel Optane DC永久内存上创建或更改区域。

### Label

Intel Optane DC内存模块支持标签，该标签允许将区域进一步划分为名称空间。标签包含存储在NVDIMM上的元数据。它类似于分区表，而命名空间是分区。

### Namespace

名称空间定义了一个非易失性存储器的连续寻址范围，该范围在概念上类似于硬盘分区，SCSI逻辑单元（LUN）或NVM Express *名称空间。它是永久内存存储的单位，在/ dev中显示为用于输入/输出（I / O）的设备。英特尔建议使用ndctl实用程序为Linux操作系统创建名称空间。

### DAX

直接访问（DAX）是一种机制，允许应用程序绕过传统的I / O堆栈（页面缓存和块层），直接从CPU（通过加载和存储）访问持久性媒体。已针对启用DAX的持久性内存进行扩展的文件系统包括Linux ext4和XFS，以及Windows NTFS。这些文件系统绕过I / O子系统，直接将持久性内存用作可字节寻址的加载/存储内存，将其作为持久性内存中存储数据的最快和最短路径。除了消除I / O操作之外，该路径还使得对小数据的写入比对传统块存储设备的写入速度更快。

## Which Mode Should I Use?

内存模式是易变的，其主要目的是以比动态随机存取存储器（DRAM）更低的成本提供大的主内存，而无需对应用程序进行任何更改，这通常可以节省成本。如果您能够将工作集放入内存中而不是将其分页到磁盘，则可能会带来性能优势。

App Direct用于持久性，您可以在其中取代传统的非易失性存储，例如固态驱动器（SSD）和NVMe设备，并且持久性存储器的速度要快得多。通常，这是很大的性能改进，但并非总是如此。如果某个应用程序倾向于从磁盘分页某些内容，然后在该页面位于DRAM中的同时使用该页面中的数据一段时间，则大多数情况下会获得DRAM速度。使用DAX文件系统时，将绕过页面缓存，从而提供对基础持久性存储器的直接访问，从而获得持久性存储器介质的性能。

因此，很难说在易失性存储模式和App Direct模式之间哪个更快。当应用程序开发人员确定哪些数据结构属于每个存储层（DRAM，持久性存储器和非易失性存储）时，性能是最佳的。

分析工具可用于表征应用程序工作负载。这有助于评估哪种模式最适合该应用程序。应在两种模式下对应用程序进行测试，以全面确定需要进行哪些优化才能实现最大性能和持久内存的优势。有关可用的持久性内存分析工具的更多信息，请访问英特尔®开发人员专区PMEM站点上的“工具”页面。

## Introduction to Provisioning Utilities

### ipmctl: Intel® Optane™ DC Persistent Memory Configuration Utility

ipmctl实用程序用于配置和管理Intel Optane DC内存模块。Linux和Microsoft Windows 2019服务器或更高版本的多个发行版中提供了此工具。

ipmctl在较高级别上支持以下功能：

-   发现
-   配置
-   固件管理
-   安全功能管理
-   健康监测
-   性能追踪
-   调试和故障排除

#### Installing ipmctl

请参阅ipmctl GitHub项目页面上的ipmctl [README.md](https://github.com/intel/ipmctl/blob/master/README.md)中的说明。

#### Getting Help

有关命令及其说明的完整列表，请运行man ipmctl或ipmctl help。

### ndctl: Namespace Management in Linux*

ndctl是与供应商无关的仅Linux实用程序，用于管理Linux中的名称空间。它旨在与来自不同供应商的NVDIMM配合使用，包括Intel Optane DC永久内存。我们将使用ndctl在Linux中创建和管理名称空间。

ndctl支持以下功能：

-   显示持久性内存模块信息
-   管理名称空间和配置标签
-   监控运行状况
-   管理安全性-密码短语和安全擦除
-   错误注入/测试

#### **Installing ndctl**

ndctl实用程序在大多数Linux软件包存储库中都可用，或者您可以下载并编译源代码，该代码可在[ndctl GitHub project page](https://github.com/pmem/ndctl)上找到。其他信息可以在《 NDCTL用户指南》中找到。

#### **Getting Help**

有关命令及其说明的完整列表，请运行man ndctl或ndctl help。

### PowerShell Cmdlets: Namespace Management in Windows*

Microsoft has introduced PowerShell* cmdlets for persistent memory namespace management. Following is a list of the most commonly used commands:

#### **Get-PmemDisk**

Returns one or more logical persistent memory disks. The returned object has information about size, atomicity type, health status, and underlying physical devices.

#### **Get-PmemPhysicalDevice**

Returns one or more physical persistent memory devices. The returned object has information about size(s), RFIC, device location, and health/operational status.

#### New-PmemDisk

Creates a new disk out of a given unused region. Writes out the labels to create the namespace, then rebuilds the SCM stacks to expose the new logical device.

#### Remove-PmemDisk

Removes the given persistent memory disk.

#### Get-PmemUnusedRegion

Returns aggregate persistent memory regions available for provisioning a logical device.

#### Initialize-PmemPhysicalDevice

Writes zeros to the label storage area, writes new label index blocks, and then rebuilds the SCM stacks to reflect the changes.

#### Getting Help

Refer to the [Interleave sets](https://docs.microsoft.com/en-us/windows-server/storage/storage-spaces/deploy-pmem#interleave-sets) section in the [Understand and deploy persistent memory](https://docs.microsoft.com/en-us/windows-server/storage/storage-spaces/deploy-pmem) Windows persistent memory PowerShell Cmdlet documentation.

### Comparison of ipmctl, ndctl and PowerShell cmdlets Features

|                      | ipmctl |     ndctl      | PowerShell* Cmds |
| :------------------: | :----: | :------------: | :--------------: |
|        vendor        | Intel  | Vendor-neutral |  Vendor-neutral  |
|        Linux*        |  Yes   |      Yes       |        No        |
|       Windows*       |  Yes   |       No       |       Yes        |
| Manage Goals/Regions |  Yes   |       No       |        No        |
|  Manage namespaces   |   No   |      Yes       |       Yes        |
|     Health/SMART     |  Yes   |      Yes       |       yes        |
|     Performance      |  Yes   |       No       |        No        |
|       Security       |  Yes   |      Yes       |        No        |

## System Requirements

需要以下硬件和软件组件：

### Hardware

基于第二代基于英特尔®至强®可扩展处理器的平台配备了英特尔®傲腾™直流内存模块和DRAM。这些平台通常有四个主要配置，分别由每个内存控制器三个通道上的内存插槽数量指定。

#### Installing Intel Optane DC Persistent Memory

要配置具有Optane DC永久内存的第二代Intel Xeon可扩展平台并获得最佳性能，请观看以下简短视频：

### Software

本节概述了为Intel DC Optane永久内存启用的软件生态系统。

#### Operating System Support for Intel Optane DC Persistent Memory

Several distributions of Linux include support for both App Direct and Memory mode. See [Operating System OS for Intel Optane DC Persistent Memory](https://www.intel.com/content/www/us/en/support/articles/000032860/memory-and-storage/data-center-persistent-memory.html).

#### Linux Kernel Support

从Linux内核4.2开始，默认情况下已启用Linux NVDIMM /永久内存驱动程序。当前，我们建议使用4.19或更高版本的内核。

##### Custom Kernel

如果编译或构建自定义内核，请确认已启用对持久性内存的支持。这是您需要在内核配置文件中启用的参数列表，通常在/ boot / config -uname -r下找到：

### Provisioning Persistent Memory Modules through the BIOS

可以使用BIOS中提供的选项来配置Intel Optane DC内存模块。请参考系统供应商提供的支持。

### Provisioning Persistent Memory Modules through UEFI

ipmctl可以从统一可扩展固件接口（UEFI）外壳启动。两种版本的ipmctl中都支持相同的功能。通过从命令行运行ipmctl help可以查看命令的完整列表。您需要root特权才能运行ipmctl。

注意：ipmctl可用于UEFI级别的名称空间创建和管理。

### Provisioning Persistent Memory Modules through Operating System

#### Using ipmctl

ipmctl可以从统一可扩展固件接口（UEFI）外壳程序或操作系统中的终端窗口启动。两种版本的ipmctl中都支持相同的功能。通过从命令行运行ipmctl help可以查看命令的完整列表。您需要root特权才能运行ipmctl。

演示了本节中描述的所有命令，以在具有6 TB持久性内存和384 GB DRAM的双插槽系统上使用。

##### Discovery

在配置Intel Optane DC内存模块之前，您可以通过show命令列表发现当前模块的状态。图1显示了一个完全填充的两路系统，通常称为2-2-2配置，总共有十二个32 GB（GiB）DDR4内存模块（DIMM）和十二个512 GiB Intel Optane DC内存模块。

##### Show Topology

show -topology命令通过枚举SMBIOS Type 17表来显示在系统中发现的Intel Optane DC永久内存和DDR4 DIMM。有关更多信息，请参阅ACPI规范v6.0或更高版本以获取NFIT表信息。

##### Show DIMM Information

show -dimm命令显示在系统中发现的永久性内存模块，并验证软件是否可以与它们通信。除其他信息外，该命令还输出每个DIMM ID，容量，运行状况和固件版本。

##### Show Provisioned Capacity

要检查为在不同操作模式下使用而准备的容量，请使用show -memoryresources命令。MemoryCapacity和AppDirectCapacity值可用于确定系统是在内存模式，App Direct模式还是混合模式下配置的。下面的示例显示持久性内存模块当前在App Direct模式下配置。

### Provisioning With ipmctl

设置Intel Optane DC永久内存是一个两步过程。在此过程中，将指定一个目标并将其存储在永久性内存模块上，以供BIOS在下次重新引导时读取。一个目标可以在内存模式和/或应用程序直接模式下配置Intel Optane DC t内存模块。

#### Create a Configuration Goal

##### Memory Mode

可以在“内存”模式下配置跨插槽的任何百分比的Intel Optane DC永久内存容量，如下所述。在此示例中，将在“内存”模式下配置100％的可用永久内存容量。您始终可以使用-f选项来覆盖任何现有目标，这是一种破坏性操作。

##### App Direct Mode

可以在App Direct模式下配置Intel Optane DC内存，并启用或禁用交错功能。如上面的“持久性内存供应概念”部分所述，交错增加了对持久性内存的读写吞吐量。

**Configure App Direct Mode with Interleaved Modules**

下面的命令设置了一个目标，以创建一个持久存储区域，该区域在每个CPU插槽上的所有模块之间交错。不允许创建跨越多个CPU插槽的交错集。有关替代方法的更多信息，请参考以下资源：

-   [Using Persistent Memory Devices with the Linux Device Mapper](https://pmem.io/2018/05/15/using_persistent_memory_devices_with_the_linux_device_mapper.html)
-   [Using Linux Volume Manager (LVM) with Persistent Memory](https://stevescargall.com/2019/05/21/using-linux-volume-manager-lvm-with-persistent-memory/)

默认的create target命令会创建一个为App Direct模式配置的交错区域。以下两个命令是等效的：

```bash
ipmctl create -goal
ipmctl create -goal PersistentMemoryType=AppDirect

The following configuration will be applied:
 SocketID | DimmID | MemorySize | AppDirect1Size | AppDirect2Size
==================================================================
 0x0000   | 0x0001 | 502.0 GiB  | 0.0 GiB        | 0.0 GiB
 0x0000   | 0x0011 | 502.0 GiB  | 0.0 GiB        | 0.0 GiB
 0x0000   | 0x0021 | 502.0 GiB  | 0.0 GiB        | 0.0 GiB
 0x0000   | 0x0101 | 502.0 GiB  | 0.0 GiB        | 0.0 GiB
 0x0000   | 0x0111 | 502.0 GiB  | 0.0 GiB        | 0.0 GiB
 0x0000   | 0x0121 | 502.0 GiB  | 0.0 GiB        | 0.0 GiB
 0x0001   | 0x1001 | 502.0 GiB  | 0.0 GiB        | 0.0 GiB
 0x0001   | 0x1011 | 502.0 GiB  | 0.0 GiB        | 0.0 GiB
 0x0001   | 0x1021 | 502.0 GiB  | 0.0 GiB        | 0.0 GiB
 0x0001   | 0x1101 | 502.0 GiB  | 0.0 GiB        | 0.0 GiB
 0x0001   | 0x1111 | 502.0 GiB  | 0.0 GiB        | 0.0 GiB
 0x0001   | 0x1121 | 502.0 GiB  | 0.0 GiB        | 0.0 GiB
Do you want to continue? [y/n]
```

https://software.intel.com/content/www/cn/zh/develop/articles/quick-start-guide-configure-intel-optane-dc-persistent-memory-on-linux.html

https://www.notion.so/Intel-Optane-Persistent-Memory-Performance-Overview-8352bb74db324ab490ee30b336108838