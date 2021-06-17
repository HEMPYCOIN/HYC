// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2015 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2020 The PIVX developers
// Copyright (c) 2021 The Hempy Coin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"

#include "chainparamsseeds.h"
#include "consensus/merkle.h"
#include "util.h"
#include "utilstrencodings.h"

#include <boost/assign/list_of.hpp>

#include <assert.h>

static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
	CMutableTransaction txNew;
	txNew.nVersion = 1;
	txNew.vin.resize(1);
	txNew.vout.resize(1);
	txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
	txNew.vout[0].nValue = genesisReward;
	txNew.vout[0].scriptPubKey = genesisOutputScript;

	CBlock genesis;
	genesis.vtx.push_back(txNew);
	genesis.hashPrevBlock.SetNull();
	genesis.nVersion = nVersion;
	genesis.nTime = nTime;
	genesis.nBits = nBits;
	genesis.nNonce = nNonce;
	genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
	return genesis;
}

/**
* Build the genesis block. Note that the output of the genesis coinbase cannot
* be spent as it did not originally exist in the database.
*
* CBlock(hash=00000ffd590b14, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=e0028e, nTime=1390095618, nBits=1e0ffff0, nNonce=28917698, vtx=1)
*   CTransaction(hash=e0028e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
*     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d01044c5957697265642030392f4a616e2f3230313420546865204772616e64204578706572696d656e7420476f6573204c6976653a204f76657273746f636b2e636f6d204973204e6f7720416363657074696e6720426974636f696e73)
*     CTxOut(nValue=50.00000000, scriptPubKey=0xA9037BAC7050C479B121CF)
*   vMerkleTree: e0028e
*/
static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
	const char* pszTimestamp = "Claim your Burger King Combo Meal";
	const CScript genesisOutputScript = CScript() << ParseHex("04f5b8143f36ad8ac63791a1bdb8f0b91a6da8c48c693a95f6c2a16cb63ea796a7960b8025a904767bc671d5dfe706a2dd2e13b86182e1064a0eca7bf863656323") << OP_CHECKSIG;
	return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

/**
* Main network
*/
/**
* What makes a good checkpoint block?
* + Is surrounded by blocks with reasonable timestamps
*   (no blocks before with a timestamp after, none after with
*    timestamp before)
* + Contains no strange transactions
*/
static Checkpoints::MapCheckpoints mapCheckpoints =
boost::assign::map_list_of
(0, uint256("0x000005b75e4097b47457d4b9e94a1db97279b57a61fb4e953557c1e6e08f9670"))
(1, uint256("0x00000aeb63891d34666fa55228ef7627efe2a087aecd2601e53ed3e0657057f7"))
(427, uint256("0x0000001dcb4614b0b0dd728a27f3e7c9c84991b1572d4322f6f6985813c6abb6"))
(965, uint256("0x0000000335039077f22b170cdb5a4f20ade0e6b62a0dba7fd731fab06451b586"))
(1048, uint256("0x5412ce319254bf19236c09ffa6f47ad9bb2999ccc3ba2b6b31ab9be042f81987"))
(2784, uint256("0x99bcbeb5798aed7b6f99f6c615d51fe0eefcaa1440fabb41e8fcc4e45fc58c2b"))
(4931, uint256("0xbf2e45fd12d3dcb3c8d8f4334ee498f5dc781cd6d0d23d887e0e29c2310a077d"))
(6254, uint256("0xccd16350f69dd0dcfd3db64596be16e3b8a42843d1cd488b1282480161e6b40e"))
(7910, uint256("0x26b2488d46e0bed76f270e2a11741d790bab6d789d02b0732bf749b3e2cecdc9"))
(10201, uint256("0xaf7ed27f6ff5a7dfd740e5e001a939a4975829983eb0029abea74169ee492a1b"))
;

static const Checkpoints::CCheckpointData data = {
	&mapCheckpoints,
	1623739320, // * UNIX timestamp of last checkpoint block
	19879,	    // * total number of transactions between genesis and last checkpoint
				//   (the tx=... number in the UpdateTip debug.log lines)
	720         // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
boost::assign::map_list_of
(0, uint256S("0x001"));
static const Checkpoints::CCheckpointData dataTestnet = {
	&mapCheckpointsTestnet,
	1591225230,
	3501914,
	3000 };

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
boost::assign::map_list_of(0, uint256S("0x001"));
static const Checkpoints::CCheckpointData dataRegtest = {
	&mapCheckpointsRegtest,
	1454124731,
	0,
	100 };

class CMainParams : public CChainParams
{
public:
	CMainParams()
	{
		networkID = CBaseChainParams::MAIN;
		strNetworkID = "main";

		genesis = CreateGenesisBlock(1622455200, 107467, 0x1e0ffff0, 1, 0);
		consensus.hashGenesisBlock = genesis.GetHash();
		assert(consensus.hashGenesisBlock == uint256S("000005b75e4097b47457d4b9e94a1db97279b57a61fb4e953557c1e6e08f9670"));
		assert(genesis.hashMerkleRoot == uint256S("e4f7704b0c1bbdaa9d62e8ea2909ad745b43f7ecb9f9d7c6291fbb93e13ba2e2")); 

		consensus.fPowAllowMinDifficultyBlocks = false;
		consensus.powLimit = ~UINT256_ZERO >> 20;   // HempyCoin starting difficulty is 1 / 2^12
		consensus.posLimitV1 = ~UINT256_ZERO >> 24;
		consensus.posLimitV2 = ~UINT256_ZERO >> 20;
		consensus.nBudgetCycleBlocks = 9999999;       // approx. 1 every 30 days
		consensus.nBudgetFeeConfirmations = 6;      // Number of confirmations for the finalization fee
		consensus.nCoinbaseMaturity = 60;
		consensus.nFutureTimeDriftPoW = 7200;
		consensus.nFutureTimeDriftPoS = 180;
		consensus.nMasternodeCountDrift = 20;       // num of MN we allow the see-saw payments to be off by
		consensus.nMaxMoneyOut = 100000000000 * COIN;
		consensus.nPoolMaxTransactions = 3;
		consensus.nProposalEstablishmentTime = 60 * 60 * 24;    // must be at least a day old to make it into a budget
		consensus.nStakeMinAge = 60 * 60;
		consensus.nStakeMinDepth = 60;
		consensus.nTargetTimespan = 40 * 60;
		consensus.nTargetTimespanV2 = 30 * 60;
		consensus.nTargetSpacing = 2 * 60;
		consensus.nTimeSlotLength = 15;

		// spork keys
		consensus.strSporkPubKey = "046fd7ea2b9102a3b9a8e8b59ed63abb06bff04bdec2f1c641ea588c9bb57e759032ef41c6bee37816eb2587fec1fe6c48c9d80ef9493dac4be7bc93c33c0b5878";
		consensus.strSporkPubKeyOld = "046fd7ea2b9102a3b9a8e8b59ed63abb06bff04bdec2f1c641ea588c9bb57e759032ef41c6bee37816eb2587fec1fe6c48c9d80ef9493dac4be7bc93c33c0b5878";
		consensus.nTime_EnforceNewSporkKey = 1622466000;    //!> Monday, 31 May 2021 1:00:00 PM GMT
		consensus.nTime_RejectOldSporkKey = 1622552400;     //!> Tuesday, 1 June 2021 1:00:00 PM GMT

		// Network upgrades
		consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight =
			Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
		consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight =
			Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
		consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight = 1001;
		consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight = 1;
		consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight = 1300;
		consensus.vUpgrades[Consensus::UPGRADE_V3_4].nActivationHeight = 1001;
		consensus.vUpgrades[Consensus::UPGRADE_V4_0].nActivationHeight = 1100;
		consensus.vUpgrades[Consensus::UPGRADE_V5_DUMMY].nActivationHeight =
			Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;

		consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock =
			uint256S("0x");
		consensus.vUpgrades[Consensus::UPGRADE_V3_4].hashActivationBlock =
			uint256S("0x");
		consensus.vUpgrades[Consensus::UPGRADE_V4_0].hashActivationBlock =
			uint256S("0x");

		/**
		* The message start string is designed to be unlikely to occur in normal data.
		* The characters are rarely used upper ASCII, not valid as UTF-8, and produce
		* a large 4-byte int at any alignment.
		*/
		pchMessageStart[0] = 0x1a;
		pchMessageStart[1] = 0x7c;
		pchMessageStart[2] = 0xd5;
		pchMessageStart[3] = 0xca;
		nDefaultPort = 2816;

		// Note that of those with the service bits flag, most only support a subset of possible options
		vSeeds.push_back(CDNSSeedData("51.222.199.80", "51.222.199.80", true));
		vSeeds.push_back(CDNSSeedData("2607:5300:60:7e92::80", "2607:5300:60:7e92::80", true));
		vSeeds.push_back(CDNSSeedData("51.222.199.81", "51.222.199.81", true));
		vSeeds.push_back(CDNSSeedData("2607:5300:60:7e92::81", "2607:5300:60:7e92::81", true));
		vSeeds.push_back(CDNSSeedData("51.222.199.82", "51.222.199.82", true));
		vSeeds.push_back(CDNSSeedData("2607:5300:60:7e92::82", "2607:5300:60:7e92::82", true));
		vSeeds.push_back(CDNSSeedData("51.222.199.83", "51.222.199.83", true));
		vSeeds.push_back(CDNSSeedData("2607:5300:60:7e92::83", "2607:5300:60:7e92::83", true));
		vSeeds.push_back(CDNSSeedData("51.222.199.84", "51.222.199.84", true));
		vSeeds.push_back(CDNSSeedData("2607:5300:60:7e92::84", "2607:5300:60:7e92::84", true));
		vSeeds.push_back(CDNSSeedData("51.222.199.85", "51.222.199.85", true));
		vSeeds.push_back(CDNSSeedData("2607:5300:60:7e92::85", "2607:5300:60:7e92::85", true));
		vSeeds.push_back(CDNSSeedData("51.222.199.86", "51.222.199.86", true));
		vSeeds.push_back(CDNSSeedData("2607:5300:60:7e92::86", "2607:5300:60:7e92::86", true));
		vSeeds.push_back(CDNSSeedData("51.222.199.87", "51.222.199.87", true));
		vSeeds.push_back(CDNSSeedData("2607:5300:60:7e92::87", "2607:5300:60:7e92::87", true));
		vSeeds.push_back(CDNSSeedData("51.222.199.88", "51.222.199.88", true));
		vSeeds.push_back(CDNSSeedData("2607:5300:60:7e92::88", "2607:5300:60:7e92::88", true));
		vSeeds.push_back(CDNSSeedData("51.222.199.89", "51.222.199.89", true));
		vSeeds.push_back(CDNSSeedData("2607:5300:60:7e92::89", "2607:5300:60:7e92::89", true));
		vSeeds.push_back(CDNSSeedData("51.222.199.90", "51.222.199.90", true));
		vSeeds.push_back(CDNSSeedData("2607:5300:60:7e92::90", "2607:5300:60:7e92::90", true));
		vSeeds.push_back(CDNSSeedData("51.222.199.91", "51.222.199.91", true));
		vSeeds.push_back(CDNSSeedData("2607:5300:60:7e92::91", "2607:5300:60:7e92::91", true));
		vSeeds.push_back(CDNSSeedData("51.222.199.92", "51.222.199.92", true));
		vSeeds.push_back(CDNSSeedData("2607:5300:60:7e92::92", "2607:5300:60:7e92::92", true));
		vSeeds.push_back(CDNSSeedData("51.222.199.93", "51.222.199.93", true));
		vSeeds.push_back(CDNSSeedData("2607:5300:60:7e92::93", "2607:5300:60:7e92::93", true));
		vSeeds.push_back(CDNSSeedData("51.222.199.94", "51.222.199.94", true));
		vSeeds.push_back(CDNSSeedData("2607:5300:60:7e92::94", "2607:5300:60:7e92::94", true));
		
		base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 40);		// H
		base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 6);
		base58Prefixes[STAKING_ADDRESS] = std::vector<unsigned char>(1, 78);	// Y
		base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 46);
		base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
		base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();
		// BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
		base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0xde).convert_to_container<std::vector<unsigned char> >();

		vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

		// Sapling
		bech32HRPs[SAPLING_PAYMENT_ADDRESS] = "ps";
		bech32HRPs[SAPLING_FULL_VIEWING_KEY] = "pviews";
		bech32HRPs[SAPLING_INCOMING_VIEWING_KEY] = "pivks";
		bech32HRPs[SAPLING_EXTENDED_SPEND_KEY] = "p-secret-spending-key-main";
	}

	const Checkpoints::CCheckpointData& Checkpoints() const
	{
		return data;
	}

};
static CMainParams mainParams;

/**
* Testnet (v3)
*/
class CTestNetParams : public CMainParams
{
public:
	CTestNetParams()
	{
		networkID = CBaseChainParams::TESTNET;
		strNetworkID = "test";

		genesis = CreateGenesisBlock(1454124731, 2402015, 0x1e0ffff0, 1, 250 * COIN);
		consensus.hashGenesisBlock = genesis.GetHash();
		//assert(consensus.hashGenesisBlock == uint256S("0x0000041e482b9b9691d98eefb48473405c0b8ec31b76df3797c74a78680ef818"));
		//assert(genesis.hashMerkleRoot == uint256S("0x1b2ef6e2f28be914103a277377ae7729dcd125dfeb8bf97bd5964ba72b6dc39b"));

		consensus.fPowAllowMinDifficultyBlocks = true;
		consensus.powLimit = ~UINT256_ZERO >> 20;   // HempyCoin starting difficulty is 1 / 2^12
		consensus.posLimitV1 = ~UINT256_ZERO >> 24;
		consensus.posLimitV2 = ~UINT256_ZERO >> 20;
		consensus.nBudgetCycleBlocks = 144;         // approx 10 cycles per day
		consensus.nBudgetFeeConfirmations = 3;      // (only 8-blocks window for finalization on testnet)
		consensus.nCoinbaseMaturity = 15;
		consensus.nFutureTimeDriftPoW = 7200;
		consensus.nFutureTimeDriftPoS = 180;
		consensus.nMasternodeCountDrift = 4;        // num of MN we allow the see-saw payments to be off by
		consensus.nMaxMoneyOut = 43199500 * COIN;
		consensus.nPoolMaxTransactions = 2;
		consensus.nProposalEstablishmentTime = 60 * 5;  // at least 5 min old to make it into a budget
		consensus.nStakeMinAge = 60 * 60;
		consensus.nStakeMinDepth = 100;
		consensus.nTargetTimespan = 40 * 60;
		consensus.nTargetTimespanV2 = 30 * 60;
		consensus.nTargetSpacing = 1 * 60;
		consensus.nTimeSlotLength = 15;

		// spork keys
		consensus.strSporkPubKey = "04E88BB455E2A04E65FCC41D88CD367E9CCE1F5A409BE94D8C2B4B35D223DED9C8E2F4E061349BA3A38839282508066B6DC4DB72DD432AC4067991E6BF20176127";
		consensus.strSporkPubKeyOld = "04A8B319388C0F8588D238B9941DC26B26D3F9465266B368A051C5C100F79306A557780101FE2192FE170D7E6DEFDCBEE4C8D533396389C0DAFFDBC842B002243C";
		consensus.nTime_EnforceNewSporkKey = 1566860400;    //!> August 26, 2019 11:00:00 PM GMT
		consensus.nTime_RejectOldSporkKey = 1569538800;     //!> September 26, 2019 11:00:00 PM GMT

															// Network upgrades
		consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight =
			Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
		consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight =
			Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
		consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight = 201;
		consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight = 51197;
		consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight = 851019;
		consensus.vUpgrades[Consensus::UPGRADE_V3_4].nActivationHeight = 1214000;
		consensus.vUpgrades[Consensus::UPGRADE_V4_0].nActivationHeight = 1347000;
		consensus.vUpgrades[Consensus::UPGRADE_V5_DUMMY].nActivationHeight =
			Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;

		consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock =
			uint256S("0xc54b3e7e8b710e4075da1806adf2d508ae722627d5bcc43f594cf64d5eef8b30");
		consensus.vUpgrades[Consensus::UPGRADE_V3_4].hashActivationBlock =
			uint256S("0x1822577176173752aea33d1f60607cefe9e0b1c54ebaa77eb40201a385506199");
		consensus.vUpgrades[Consensus::UPGRADE_V4_0].hashActivationBlock =
			uint256S("0x30c173ffc09a13f288bf6e828216107037ce5b79536b1cebd750a014f4939882");

		/**
		* The message start string is designed to be unlikely to occur in normal data.
		* The characters are rarely used upper ASCII, not valid as UTF-8, and produce
		* a large 4-byte int at any alignment.
		*/

		pchMessageStart[0] = 0x45;
		pchMessageStart[1] = 0x76;
		pchMessageStart[2] = 0x65;
		pchMessageStart[3] = 0xba;
		nDefaultPort = 51474;

		vFixedSeeds.clear();
		vSeeds.clear();
		// nodes with support for servicebits filtering should be at the top
		vSeeds.push_back(CDNSSeedData("fuzzbawls.pw", "hempycoin-testnet.seed.fuzzbawls.pw", true));
		vSeeds.push_back(CDNSSeedData("fuzzbawls.pw", "hempycoin-testnet.seed2.fuzzbawls.pw", true));

		base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet hempycoin addresses start with 'x' or 'y'
		base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet hempycoin script addresses start with '8' or '9'
		base58Prefixes[STAKING_ADDRESS] = std::vector<unsigned char>(1, 73);     // starting with 'W'
		base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
																			 // Testnet hempycoin BIP32 pubkeys start with 'DRKV'
		base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
		// Testnet hempycoin BIP32 prvkeys start with 'DRKP'
		base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
		// Testnet hempycoin BIP44 coin type is '1' (All coin's testnet default)
		base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

		vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

		// Sapling
		bech32HRPs[SAPLING_PAYMENT_ADDRESS] = "ptestsapling";
		bech32HRPs[SAPLING_FULL_VIEWING_KEY] = "pviewtestsapling";
		bech32HRPs[SAPLING_INCOMING_VIEWING_KEY] = "bcktestsapling";
		bech32HRPs[SAPLING_EXTENDED_SPEND_KEY] = "p-secret-spending-key-test";
	}

	const Checkpoints::CCheckpointData& Checkpoints() const
	{
		return dataTestnet;
	}
};
static CTestNetParams testNetParams;

/**
* Regression test
*/
class CRegTestParams : public CTestNetParams
{
public:
	CRegTestParams()
	{
		networkID = CBaseChainParams::REGTEST;
		strNetworkID = "regtest";

		genesis = CreateGenesisBlock(1454124731, 2402015, 0x1e0ffff0, 1, 250 * COIN);
		consensus.hashGenesisBlock = genesis.GetHash();
		//assert(consensus.hashGenesisBlock == uint256S("0x0000041e482b9b9691d98eefb48473405c0b8ec31b76df3797c74a78680ef818"));
		//assert(genesis.hashMerkleRoot == uint256S("0x1b2ef6e2f28be914103a277377ae7729dcd125dfeb8bf97bd5964ba72b6dc39b"));

		consensus.fPowAllowMinDifficultyBlocks = true;
		consensus.powLimit = ~UINT256_ZERO >> 20;   // HempyCoin starting difficulty is 1 / 2^12
		consensus.posLimitV1 = ~UINT256_ZERO >> 24;
		consensus.posLimitV2 = ~UINT256_ZERO >> 20;
		consensus.nBudgetCycleBlocks = 144;         // approx 10 cycles per day
		consensus.nBudgetFeeConfirmations = 3;      // (only 8-blocks window for finalization on regtest)
		consensus.nCoinbaseMaturity = 100;
		consensus.nFutureTimeDriftPoW = 7200;
		consensus.nFutureTimeDriftPoS = 180;
		consensus.nMasternodeCountDrift = 4;        // num of MN we allow the see-saw payments to be off by
		consensus.nMaxMoneyOut = 43199500 * COIN;
		consensus.nPoolMaxTransactions = 2;
		consensus.nProposalEstablishmentTime = 60 * 5;  // at least 5 min old to make it into a budget
		consensus.nStakeMinAge = 0;
		consensus.nStakeMinDepth = 2;
		consensus.nTargetTimespan = 40 * 60;
		consensus.nTargetTimespanV2 = 30 * 60;
		consensus.nTargetSpacing = 1 * 60;
		consensus.nTimeSlotLength = 15;

		/* Spork Key for RegTest:
		WIF private key: 932HEevBSujW2ud7RfB1YF91AFygbBRQj3de3LyaCRqNzKKgWXi
		private key hex: bd4960dcbd9e7f2223f24e7164ecb6f1fe96fc3a416f5d3a830ba5720c84b8ca
		Address: yCvUVd72w7xpimf981m114FSFbmAmne7j9
		*/
		consensus.strSporkPubKey = "043969b1b0e6f327de37f297a015d37e2235eaaeeb3933deecd8162c075cee0207b13537618bde640879606001a8136091c62ec272dd0133424a178704e6e75bb7";
		consensus.strSporkPubKeyOld = "";
		consensus.nTime_EnforceNewSporkKey = 0;
		consensus.nTime_RejectOldSporkKey = 0;

		// Network upgrades
		consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight =
			Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
		consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight =
			Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
		consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight = 251;
		consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight = 251;
		consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight =
			Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
		consensus.vUpgrades[Consensus::UPGRADE_V3_4].nActivationHeight = 251;
		consensus.vUpgrades[Consensus::UPGRADE_V4_0].nActivationHeight =
			Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
		consensus.vUpgrades[Consensus::UPGRADE_V5_DUMMY].nActivationHeight = 300;

		/**
		* The message start string is designed to be unlikely to occur in normal data.
		* The characters are rarely used upper ASCII, not valid as UTF-8, and produce
		* a large 4-byte int at any alignment.
		*/

		pchMessageStart[0] = 0xa1;
		pchMessageStart[1] = 0xcf;
		pchMessageStart[2] = 0x7e;
		pchMessageStart[3] = 0xac;
		nDefaultPort = 51476;

		vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
		vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.
	}

	const Checkpoints::CCheckpointData& Checkpoints() const
	{
		return dataRegtest;
	}

	void UpdateNetworkUpgradeParameters(Consensus::UpgradeIndex idx, int nActivationHeight)
	{
		assert(idx > Consensus::BASE_NETWORK && idx < Consensus::MAX_NETWORK_UPGRADES);
		consensus.vUpgrades[idx].nActivationHeight = nActivationHeight;
	}
};
static CRegTestParams regTestParams;

static CChainParams* pCurrentParams = 0;

const CChainParams& Params()
{
	assert(pCurrentParams);
	return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
	switch (network) {
	case CBaseChainParams::MAIN:
		return mainParams;
	case CBaseChainParams::TESTNET:
		return testNetParams;
	case CBaseChainParams::REGTEST:
		return regTestParams;
	default:
		assert(false && "Unimplemented network");
		return mainParams;
	}
}

void SelectParams(CBaseChainParams::Network network)
{
	SelectBaseParams(network);
	pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
	CBaseChainParams::Network network = NetworkIdFromCommandLine();
	if (network == CBaseChainParams::MAX_NETWORK_TYPES)
		return false;

	SelectParams(network);
	return true;
}

void UpdateNetworkUpgradeParameters(Consensus::UpgradeIndex idx, int nActivationHeight)
{
	regTestParams.UpdateNetworkUpgradeParameters(idx, nActivationHeight);
}
