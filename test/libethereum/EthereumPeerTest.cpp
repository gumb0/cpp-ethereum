/*
	This file is part of cpp-ethereum.

	cpp-ethereum is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	cpp-ethereum is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with cpp-ethereum.  If not, see <http://www.gnu.org/licenses/>.
*/
/** @file 
 * @author 
 * @date 
 * Peer test functions.
 */

#include <libethereum/EthereumPeer.h>
#include <test/TestHelper.h>

using namespace std;
using namespace dev;
using namespace dev::eth;
using namespace dev::p2p;
using namespace dev::test;

class MockHostCapability : public p2p::HostCapabilityFace
{
protected:
	string name() const override { return "mock capability name"; }
	u256 version() const override { return 0; }
	unsigned messageCount() const override { return 0;  }
	shared_ptr<p2p::Capability> newPeerCapability(std::shared_ptr<p2p::SessionFace> const& _s, unsigned _idOffset, p2p::CapDesc const& _cap, uint16_t _capID) override { return shared_ptr<p2p::Capability>(); }
};

class MockSession : public p2p::SessionFace
{
public:
	void start() override { }
	void disconnect(DisconnectReason _reason) override { }

	void ping() override { }

	bool isConnected() const override { return true; }

	NodeID id() const override { return {}; }

	void sealAndSend(RLPStream& _s, uint16_t _protocolID) override { }

	int rating() const override { return 0; }
	void addRating(int _r) override { }

	void addNote(std::string const& _k, std::string const& _v) override { }

	PeerSessionInfo info() const override { return PeerSessionInfo{ NodeID{}, "", "", 0, std::chrono::steady_clock::duration{}, {}, 0, {}, 0 }; }
	std::chrono::steady_clock::time_point connectionTime() override { return std::chrono::steady_clock::time_point{}; }

	void registerCapability(CapDesc const& _desc, std::shared_ptr<Capability> _p) override { }
	void registerFraming(uint16_t _id) override { }

	std::map<CapDesc, std::shared_ptr<Capability>> const &  capabilities() const override { return m_capabilities; }

	std::shared_ptr<Peer> peer() const override { return std::shared_ptr<Peer>();  }

	std::chrono::steady_clock::time_point lastReceived() const override { return std::chrono::steady_clock::time_point{}; }

	std::map<CapDesc, std::shared_ptr<Capability>> m_capabilities;
};


BOOST_FIXTURE_TEST_SUITE(EthereumPeerSuite, TestOutputHelper)

BOOST_AUTO_TEST_CASE(EthereumPeerSuite_requestNodeData)
{
	MockHostCapability hostCap;
	EthereumPeer peer(shared_ptr<p2p::SessionFace>(new MockSession()), &hostCap, 0, {"", 0}, 0);
	peer.requestNodeData({u256("0x949d991d685738352398dff73219ab19c62c06e6f8ce899fbae755d5127ed1ef")});


}


BOOST_AUTO_TEST_SUITE_END()
