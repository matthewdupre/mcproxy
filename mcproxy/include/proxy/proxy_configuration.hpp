/*
 * This file is part of mcproxy.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * written by Sebastian Woelke, in cooperation with:
 * INET group, Hamburg University of Applied Sciences,
 * Website: http://mcproxy.realmv6.org/
 */

#ifndef PROXY_CONFIGURATION_HPP
#define PROXY_CONFIGURATION_HPP

#include "include/proxy/interfaces.hpp"

#include <memory>
#include <set>


/**
 * @brief Default path to find the config file.
 */
#define PROXY_CONFIGURATION_DEFAULT_CONIG_PATH "mcproxy.conf"

/**
 * @brief Downstream vector for #up_down_map.
 * @param vector of the downstream interfaces indexes
 */
using downstream_set = std::set<unsigned int>;

/**
 * @brief data structure to mangage the upstream/downstream instances.
 * @param first index of the upstream interface
 * @param second index vector of the downstream interfaces
 */
using upstream_downstream_map = std::map<unsigned int, downstream_set>; //map<upstream, downstreams>

/**
 * @brief Pair for #up_down_map.
 * @param first index of the upstream interface
 * @param second vector of the downstream interfaces
 */
using upstream_downsteram_pair = std::pair<unsigned int, downstream_set>;


class proxy_configuration
{
private:
    const shared_ptr<interfaces> m_interfaces;
    int m_addr_family; //AF_INET or AF_INET6
    int m_version; //for AF_INET (1,2,3) to use IGMPv1/2/3, for AF_INET6 (1,2) to use MLDv1/2
    upstream_downstream_map m_upstream_downstream_map;

    bool parse_config(const std::string& path);
    bool check_interface_flags(upstream_downstream_map& udm); //check up and running flag, set multicast and allMulti flag
    bool check_double_used_if(upstream_downstream_map& udm);

public:
    proxy_configuration(const shared_ptr<interfaces> interfaces);
    ~proxy_configuration();

    bool load_config(const std::string& path);
    std::string get_parsed_state() const;
};

#endif // PROXY_CONFIGURATION_HPP
