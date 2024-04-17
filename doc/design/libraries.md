# Libraries

| Name                     | Description |
|--------------------------|-------------|
| *libbitcoinluminary_cli*         | RPC client functionality used by *bitcoinluminary-cli* executable |
| *libbitcoinluminary_common*      | Home for common functionality shared by different executables and libraries. Similar to *libbitcoinluminary_util*, but higher-level (see [Dependencies](#dependencies)). |
| *libbitcoinluminary_consensus*   | Stable, backwards-compatible consensus functionality used by *libbitcoinluminary_node* and *libbitcoinluminary_wallet* and also exposed as a [shared library](../shared-libraries.md). |
| *libbitcoinluminaryconsensus*    | Shared library build of static *libbitcoinluminary_consensus* library |
| *libbitcoinluminary_kernel*      | Consensus engine and support library used for validation by *libbitcoinluminary_node* and also exposed as a [shared library](../shared-libraries.md). |
| *libbitcoinluminaryqt*           | GUI functionality used by *bitcoinluminary-qt* and *bitcoinluminary-gui* executables |
| *libbitcoinluminary_ipc*         | IPC functionality used by *bitcoinluminary-node*, *bitcoinluminary-wallet*, *bitcoinluminary-gui* executables to communicate when [`--enable-multiprocess`](multiprocess.md) is used. |
| *libbitcoinluminary_node*        | P2P and RPC server functionality used by *bitcoinluminaryd* and *bitcoinluminary-qt* executables. |
| *libbitcoinluminary_util*        | Home for common functionality shared by different executables and libraries. Similar to *libbitcoinluminary_common*, but lower-level (see [Dependencies](#dependencies)). |
| *libbitcoinluminary_wallet*      | Wallet functionality used by *bitcoinluminaryd* and *bitcoinluminary-wallet* executables. |
| *libbitcoinluminary_wallet_tool* | Lower-level wallet functionality used by *bitcoinluminary-wallet* executable. |
| *libbitcoinluminary_zmq*         | [ZeroMQ](../zmq.md) functionality used by *bitcoinluminaryd* and *bitcoinluminary-qt* executables. |

## Conventions

- Most libraries are internal libraries and have APIs which are completely unstable! There are few or no restrictions on backwards compatibility or rules about external dependencies. Exceptions are *libbitcoinluminary_consensus* and *libbitcoinluminary_kernel* which have external interfaces documented at [../shared-libraries.md](../shared-libraries.md).

- Generally each library should have a corresponding source directory and namespace. Source code organization is a work in progress, so it is true that some namespaces are applied inconsistently, and if you look at [`libbitcoinluminary_*_SOURCES`](../../src/Makefile.am) lists you can see that many libraries pull in files from outside their source directory. But when working with libraries, it is good to follow a consistent pattern like:

  - *libbitcoinluminary_node* code lives in `src/node/` in the `node::` namespace
  - *libbitcoinluminary_wallet* code lives in `src/wallet/` in the `wallet::` namespace
  - *libbitcoinluminary_ipc* code lives in `src/ipc/` in the `ipc::` namespace
  - *libbitcoinluminary_util* code lives in `src/util/` in the `util::` namespace
  - *libbitcoinluminary_consensus* code lives in `src/consensus/` in the `Consensus::` namespace

## Dependencies

- Libraries should minimize what other libraries they depend on, and only reference symbols following the arrows shown in the dependency graph below:

<table><tr><td>

```mermaid

%%{ init : { "flowchart" : { "curve" : "basis" }}}%%

graph TD;

bitcoinluminary-cli[bitcoinluminary-cli]-->libbitcoinluminary_cli;

bitcoinluminaryd[bitcoinluminaryd]-->libbitcoinluminary_node;
bitcoinluminaryd[bitcoinluminaryd]-->libbitcoinluminary_wallet;

bitcoinluminary-qt[bitcoinluminary-qt]-->libbitcoinluminary_node;
bitcoinluminary-qt[bitcoinluminary-qt]-->libbitcoinluminaryqt;
bitcoinluminary-qt[bitcoinluminary-qt]-->libbitcoinluminary_wallet;

bitcoinluminary-wallet[bitcoinluminary-wallet]-->libbitcoinluminary_wallet;
bitcoinluminary-wallet[bitcoinluminary-wallet]-->libbitcoinluminary_wallet_tool;

libbitcoinluminary_cli-->libbitcoinluminary_util;
libbitcoinluminary_cli-->libbitcoinluminary_common;

libbitcoinluminary_common-->libbitcoinluminary_consensus;
libbitcoinluminary_common-->libbitcoinluminary_util;

libbitcoinluminary_kernel-->libbitcoinluminary_consensus;
libbitcoinluminary_kernel-->libbitcoinluminary_util;

libbitcoinluminary_node-->libbitcoinluminary_consensus;
libbitcoinluminary_node-->libbitcoinluminary_kernel;
libbitcoinluminary_node-->libbitcoinluminary_common;
libbitcoinluminary_node-->libbitcoinluminary_util;

libbitcoinluminaryqt-->libbitcoinluminary_common;
libbitcoinluminaryqt-->libbitcoinluminary_util;

libbitcoinluminary_wallet-->libbitcoinluminary_common;
libbitcoinluminary_wallet-->libbitcoinluminary_util;

libbitcoinluminary_wallet_tool-->libbitcoinluminary_wallet;
libbitcoinluminary_wallet_tool-->libbitcoinluminary_util;

classDef bold stroke-width:2px, font-weight:bold, font-size: smaller;
class bitcoinluminary-qt,bitcoinluminaryd,bitcoinluminary-cli,bitcoinluminary-wallet bold
```
</td></tr><tr><td>

**Dependency graph**. Arrows show linker symbol dependencies. *Consensus* lib depends on nothing. *Util* lib is depended on by everything. *Kernel* lib depends only on consensus and util.

</td></tr></table>

- The graph shows what _linker symbols_ (functions and variables) from each library other libraries can call and reference directly, but it is not a call graph. For example, there is no arrow connecting *libbitcoinluminary_wallet* and *libbitcoinluminary_node* libraries, because these libraries are intended to be modular and not depend on each other's internal implementation details. But wallet code is still able to call node code indirectly through the `interfaces::Chain` abstract class in [`interfaces/chain.h`](../../src/interfaces/chain.h) and node code calls wallet code through the `interfaces::ChainClient` and `interfaces::Chain::Notifications` abstract classes in the same file. In general, defining abstract classes in [`src/interfaces/`](../../src/interfaces/) can be a convenient way of avoiding unwanted direct dependencies or circular dependencies between libraries.

- *libbitcoinluminary_consensus* should be a standalone dependency that any library can depend on, and it should not depend on any other libraries itself.

- *libbitcoinluminary_util* should also be a standalone dependency that any library can depend on, and it should not depend on other internal libraries.

- *libbitcoinluminary_common* should serve a similar function as *libbitcoinluminary_util* and be a place for miscellaneous code used by various daemon, GUI, and CLI applications and libraries to live. It should not depend on anything other than *libbitcoinluminary_util* and *libbitcoinluminary_consensus*. The boundary between _util_ and _common_ is a little fuzzy but historically _util_ has been used for more generic, lower-level things like parsing hex, and _common_ has been used for bitcoinluminary-specific, higher-level things like parsing base58. The difference between util and common is mostly important because *libbitcoinluminary_kernel* is not supposed to depend on *libbitcoinluminary_common*, only *libbitcoinluminary_util*. In general, if it is ever unclear whether it is better to add code to *util* or *common*, it is probably better to add it to *common* unless it is very generically useful or useful particularly to include in the kernel.


- *libbitcoinluminary_kernel* should only depend on *libbitcoinluminary_util* and *libbitcoinluminary_consensus*.

- The only thing that should depend on *libbitcoinluminary_kernel* internally should be *libbitcoinluminary_node*. GUI and wallet libraries *libbitcoinluminaryqt* and *libbitcoinluminary_wallet* in particular should not depend on *libbitcoinluminary_kernel* and the unneeded functionality it would pull in, like block validation. To the extent that GUI and wallet code need scripting and signing functionality, they should be get able it from *libbitcoinluminary_consensus*, *libbitcoinluminary_common*, and *libbitcoinluminary_util*, instead of *libbitcoinluminary_kernel*.

- GUI, node, and wallet code internal implementations should all be independent of each other, and the *libbitcoinluminaryqt*, *libbitcoinluminary_node*, *libbitcoinluminary_wallet* libraries should never reference each other's symbols. They should only call each other through [`src/interfaces/`](`../../src/interfaces/`) abstract interfaces.

## Work in progress

- Validation code is moving from *libbitcoinluminary_node* to *libbitcoinluminary_kernel* as part of [The libbitcoinluminarykernel Project #24303](https://github.com/bitcoinluminary/bitcoinluminary/issues/24303)
- Source code organization is discussed in general in [Library source code organization #15732](https://github.com/bitcoinluminary/bitcoinluminary/issues/15732)
