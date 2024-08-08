FROM alpine:latest

ARG datadir=data
ARG shell=zsh
ARG username=fibonacci
ARG hostname=FRAT

RUN apk add --no-cache openssh
RUN apk add --no-cache ${shell}

RUN adduser -D -s /bin/${shell} -h /home/${username} ${username}
RUN echo "${username}:*" | chpasswd -e
RUN echo "${hostname}" > /etc/hostname
COPY ${datadir}/.${shell}rc /home/${username}
RUN chown -R ${username}:${username} /home/${username}
RUN chmod 700 /home/${username}
RUN chown -R root /home/${username}/.${shell}rc
RUN chmod 550 /home/${username}/.${shell}rc
# COPY ${datadir}/single.${shell} /bin
# RUN chmod 755 /bin/single.${shell}

COPY ${datadir}/sshd_config /etc/ssh/sshd_config
COPY ${datadir}/id_ed25519_fibonacci.pub /etc/ssh/authorized_keys
RUN chmod 644 /etc/ssh/authorized_keys
COPY ${datadir}/ssh_host_ed25519_key /etc/ssh/ssh_host_ed25519_key
RUN chmod 600 /etc/ssh/ssh_host_ed25519_key
COPY ${datadir}/ssh_host_ed25519_key.pub /etc/ssh/ssh_host_ed25519_key.pub
RUN chmod 644 /etc/ssh/ssh_host_ed25519_key.pub

EXPOSE 2222:22/tcp

CMD ["/usr/sbin/sshd", "-D", "-e", "-f", "/etc/ssh/sshd_config"]
