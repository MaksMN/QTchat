--
-- PostgreSQL database dump
--

-- Dumped from database version 16.0
-- Dumped by pg_dump version 16.0

-- Started on 2023-10-17 18:41:34

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET xmloption = content;
SET client_min_messages = warning;
SET row_security = off;

--
-- TOC entry 221 (class 1255 OID 16472)
-- Name: del_user(); Type: FUNCTION; Schema: public; Owner: qt_chat
--

CREATE FUNCTION public.del_user() RETURNS trigger
    LANGUAGE plpgsql
    AS $$begin
UPDATE public.pub_messages 
SET status=((SELECT status WHERE author_id=old.id)|16) 
WHERE author_id=old.id;
RETURN OLD;
end;$$;


ALTER FUNCTION public.del_user() OWNER TO qt_chat;

SET default_tablespace = '';

SET default_table_access_method = heap;

--
-- TOC entry 215 (class 1259 OID 16550)
-- Name: private_messages; Type: TABLE; Schema: public; Owner: qt_chat
--

CREATE TABLE public.private_messages (
    id bigint NOT NULL,
    author_id bigint,
    recipient_id bigint,
    text text,
    published bigint,
    status integer
);


ALTER TABLE public.private_messages OWNER TO qt_chat;

--
-- TOC entry 220 (class 1259 OID 16598)
-- Name: private_messages_id_seq; Type: SEQUENCE; Schema: public; Owner: qt_chat
--

ALTER TABLE public.private_messages ALTER COLUMN id ADD GENERATED ALWAYS AS IDENTITY (
    SEQUENCE NAME public.private_messages_id_seq
    START WITH 0
    INCREMENT BY 1
    MINVALUE 0
    NO MAXVALUE
    CACHE 1
);


--
-- TOC entry 216 (class 1259 OID 16555)
-- Name: pub_messages; Type: TABLE; Schema: public; Owner: qt_chat
--

CREATE TABLE public.pub_messages (
    id bigint NOT NULL,
    author_id bigint,
    text text NOT NULL,
    published bigint,
    status integer NOT NULL
);


ALTER TABLE public.pub_messages OWNER TO qt_chat;

--
-- TOC entry 219 (class 1259 OID 16596)
-- Name: pub_messages_id_seq; Type: SEQUENCE; Schema: public; Owner: qt_chat
--

ALTER TABLE public.pub_messages ALTER COLUMN id ADD GENERATED ALWAYS AS IDENTITY (
    SEQUENCE NAME public.pub_messages_id_seq
    START WITH 0
    INCREMENT BY 1
    MINVALUE 0
    NO MAXVALUE
    CACHE 1
);


--
-- TOC entry 217 (class 1259 OID 16560)
-- Name: users; Type: TABLE; Schema: public; Owner: qt_chat
--

CREATE TABLE public.users (
    id bigint NOT NULL,
    login character varying(20) NOT NULL,
    email character varying(100) NOT NULL,
    first_name character varying(100) NOT NULL,
    last_name character varying(100),
    registered bigint DEFAULT 0,
    status integer DEFAULT 2,
    session_key bigint DEFAULT 0,
    hash character varying(40) DEFAULT 0 NOT NULL,
    salt character varying(40) DEFAULT 0 NOT NULL
);


ALTER TABLE public.users OWNER TO qt_chat;

--
-- TOC entry 218 (class 1259 OID 16568)
-- Name: users_id_seq; Type: SEQUENCE; Schema: public; Owner: qt_chat
--

ALTER TABLE public.users ALTER COLUMN id ADD GENERATED ALWAYS AS IDENTITY (
    SEQUENCE NAME public.users_id_seq
    START WITH 0
    INCREMENT BY 1
    MINVALUE 0
    NO MAXVALUE
    CACHE 1
);


--
-- TOC entry 4862 (class 0 OID 16550)
-- Dependencies: 215
-- Data for Name: private_messages; Type: TABLE DATA; Schema: public; Owner: qt_chat
--

COPY public.private_messages (id, author_id, recipient_id, text, published, status) FROM stdin;
\.


--
-- TOC entry 4863 (class 0 OID 16555)
-- Dependencies: 216
-- Data for Name: pub_messages; Type: TABLE DATA; Schema: public; Owner: qt_chat
--

COPY public.pub_messages (id, author_id, text, published, status) FROM stdin;
\.


--
-- TOC entry 4864 (class 0 OID 16560)
-- Dependencies: 217
-- Data for Name: users; Type: TABLE DATA; Schema: public; Owner: qt_chat
--

COPY public.users (id, login, email, first_name, last_name, registered, status, session_key, hash, salt) FROM stdin;
1	admin	admin@admin	Администратор	Администраторов	0	1	0	2cfee2bd8b52a3800e594c6aae4deff49b6ac690	019UL67jUe3u9js7LKDz00QKUXuwMSM24m5Y062I
\.


--
-- TOC entry 4873 (class 0 OID 0)
-- Dependencies: 220
-- Name: private_messages_id_seq; Type: SEQUENCE SET; Schema: public; Owner: qt_chat
--

SELECT pg_catalog.setval('public.private_messages_id_seq', 0, false);


--
-- TOC entry 4874 (class 0 OID 0)
-- Dependencies: 219
-- Name: pub_messages_id_seq; Type: SEQUENCE SET; Schema: public; Owner: qt_chat
--

SELECT pg_catalog.setval('public.pub_messages_id_seq', 0, false);


--
-- TOC entry 4875 (class 0 OID 0)
-- Dependencies: 218
-- Name: users_id_seq; Type: SEQUENCE SET; Schema: public; Owner: qt_chat
--

SELECT pg_catalog.setval('public.users_id_seq', 0, false);


--
-- TOC entry 4706 (class 2606 OID 16570)
-- Name: private_messages private_messages_pk; Type: CONSTRAINT; Schema: public; Owner: qt_chat
--

ALTER TABLE ONLY public.private_messages
    ADD CONSTRAINT private_messages_pk PRIMARY KEY (id);


--
-- TOC entry 4709 (class 2606 OID 16572)
-- Name: pub_messages pub_messages_pk; Type: CONSTRAINT; Schema: public; Owner: qt_chat
--

ALTER TABLE ONLY public.pub_messages
    ADD CONSTRAINT pub_messages_pk PRIMARY KEY (id);


--
-- TOC entry 4714 (class 2606 OID 16574)
-- Name: users users_pk; Type: CONSTRAINT; Schema: public; Owner: qt_chat
--

ALTER TABLE ONLY public.users
    ADD CONSTRAINT users_pk PRIMARY KEY (id);


--
-- TOC entry 4704 (class 1259 OID 16575)
-- Name: private_messages_id_idx; Type: INDEX; Schema: public; Owner: qt_chat
--

CREATE UNIQUE INDEX private_messages_id_idx ON public.private_messages USING btree (id);


--
-- TOC entry 4707 (class 1259 OID 16576)
-- Name: pub_messages_id_idx; Type: INDEX; Schema: public; Owner: qt_chat
--

CREATE UNIQUE INDEX pub_messages_id_idx ON public.pub_messages USING btree (id);


--
-- TOC entry 4710 (class 1259 OID 16577)
-- Name: users_email_idx; Type: INDEX; Schema: public; Owner: qt_chat
--

CREATE UNIQUE INDEX users_email_idx ON public.users USING btree (email);


--
-- TOC entry 4711 (class 1259 OID 16578)
-- Name: users_id_idx; Type: INDEX; Schema: public; Owner: qt_chat
--

CREATE UNIQUE INDEX users_id_idx ON public.users USING btree (id);


--
-- TOC entry 4712 (class 1259 OID 16579)
-- Name: users_login_idx; Type: INDEX; Schema: public; Owner: qt_chat
--

CREATE UNIQUE INDEX users_login_idx ON public.users USING btree (login);


--
-- TOC entry 4718 (class 2620 OID 16580)
-- Name: users after_delete; Type: TRIGGER; Schema: public; Owner: qt_chat
--

CREATE TRIGGER after_delete BEFORE DELETE ON public.users FOR EACH ROW EXECUTE FUNCTION public.del_user();


--
-- TOC entry 4715 (class 2606 OID 16581)
-- Name: private_messages private_messages_fk; Type: FK CONSTRAINT; Schema: public; Owner: qt_chat
--

ALTER TABLE ONLY public.private_messages
    ADD CONSTRAINT private_messages_fk FOREIGN KEY (author_id) REFERENCES public.users(id) ON UPDATE CASCADE ON DELETE CASCADE;


--
-- TOC entry 4716 (class 2606 OID 16586)
-- Name: private_messages private_messages_fk2; Type: FK CONSTRAINT; Schema: public; Owner: qt_chat
--

ALTER TABLE ONLY public.private_messages
    ADD CONSTRAINT private_messages_fk2 FOREIGN KEY (recipient_id) REFERENCES public.users(id) ON UPDATE CASCADE ON DELETE CASCADE;


--
-- TOC entry 4717 (class 2606 OID 16591)
-- Name: pub_messages pub_messages_fk; Type: FK CONSTRAINT; Schema: public; Owner: qt_chat
--

ALTER TABLE ONLY public.pub_messages
    ADD CONSTRAINT pub_messages_fk FOREIGN KEY (author_id) REFERENCES public.users(id) ON UPDATE CASCADE ON DELETE SET NULL;


-- Completed on 2023-10-17 18:41:34

--
-- PostgreSQL database dump complete
--

